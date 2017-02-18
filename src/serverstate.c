#include "serverstate.h"

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>

#define CERT_FILE "keys/cacert.pem"
#define KEY_FILE "keys/cakey.pem"

static void tlsReadMany(struct tls* context, void** buf, size_t* l) {
  size_t cap = 256;
  size_t size = 0;
  size_t read;
  char tbuf[256];
  void* buffer = malloc(cap);
  do {
    read = tls_read(context, tbuf, 256);
    if (read == TLS_WANT_POLLIN || read == TLS_WANT_POLLOUT)
      continue;
    assert(read != -1);
    if (read + size > cap) {
      while (read + size > cap) cap <<= 1;
      buffer = realloc(buffer, cap);
    }
    memcpy(((char*) buffer) + size, tbuf, read);
    size += read;
  } while (read > 0);
  *buf = buffer;
  *l = size;
}

void ServerState_initialise(ServerState* state) {
  int stat;
  state->config = tls_config_new();
  if (state->config == NULL) {
    fprintf(stderr, "Could not create a TLS config\n");
    exit(-1);
  }
  tls_config_set_protocols(state->config, TLS_PROTOCOLS_DEFAULT);
  stat = tls_config_set_cert_file(state->config, CERT_FILE);
  if (stat < 0) {
    fprintf(stderr, "Could not read certificate file\n");
    exit(-1);
  }
  stat = tls_config_set_ca_file(state->config, CERT_FILE);
  if (stat < 0) {
    fprintf(stderr, "Could not read CA file\n");
    exit(-1);
  }
  stat = tls_config_set_key_file(state->config, KEY_FILE);
  if (stat < 0) {
    fprintf(stderr, "Could not read key file\n");
    exit(-1);
  }
  state->context = tls_server();
  if (state->context == NULL) {
    fprintf(stderr, "Could not create a TLS context\n");
    exit(-1);
  }
  stat = tls_configure(state->context, state->config);
  if (stat < 0) {
    fprintf(stderr, "Could not call tls_configure\n");
    exit(-1);
  }
  int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (fd < 0) {
    fprintf(stderr, "Could not create socket: error %d\n", errno);
    exit(-1);
  }
  struct sockaddr_in address = {0};
  address.sin_family = AF_INET;
  address.sin_port = htons(5835);
  address.sin_addr.s_addr = INADDR_ANY;
  stat = bind(fd, (struct sockaddr*) &address, sizeof(address));
  if (stat < 0) {
    fprintf(stderr, "Could not bind socket: error %d\n", errno);
    exit(-1);
  }
  stat = listen(fd, 128);
  if (stat < 0) {
    fprintf(stderr, "Could not listen with socket: error %d\n", errno);
    exit(-1);
  }
  state->sock = fd;
}

void ServerState_destroy(ServerState* state) {
  tls_close(state->context);
  tls_free(state->context);
  tls_config_free(state->config);
}

void ServerState_listenOnce(ServerState* state) {
  int stat;
  struct sockaddr_in incomingAddress;
  socklen_t size = sizeof(incomingAddress);
  int incomingSocket = accept(state->sock,
    (struct sockaddr*) &incomingAddress, &size);
  if (incomingSocket < 0) {
    fprintf(stderr, "Could not accept socket: error %d\n", errno);
    return;
  }
  struct tls* newContext;
  stat = tls_accept_socket(state->context, &newContext, incomingSocket);
  if (stat < 0) {
    fprintf(stderr, "Could not accept socket\n");
    return;
  }
  void* buffer;
  size_t length;
  tlsReadMany(newContext, &buffer, &length);
  tls_close(newContext);
  tls_free(newContext);
}

#include "sockutil.h"

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>

void tlsReadMany(struct tls* context, void** buf, size_t* l) {
  size_t cap = 256;
  size_t size = 0;
  int read;
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

void tlsWriteMany(struct tls* context, const void* buffer, size_t len) {
  const char* buf = buffer;
  while (len > 0) {
    ssize_t written = tls_write(context, buf, len);
    if (written == TLS_WANT_POLLIN || written == TLS_WANT_POLLOUT)
      continue;
    assert(written != -1);
    buf += written;
    len -= written;
  }
}

void tlsWriteString(struct tls* context, const char* string) {
  tlsWriteMany(context, string, strlen(string));
}
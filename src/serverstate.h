#pragma once

#include <sys/socket.h>
#include <tls.h>

typedef struct ServerState {
  struct tls_config* config;
  struct tls* context;
  socklen_t sock;
} ServerState;

void ServerState_initialise(ServerState* state);

void ServerState_destroy(ServerState* state);

void ServerState_listenOnce(ServerState* state);
#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <sqlite3.h>
#include <tls.h>
#define SHA2_USE_INTTYPES_H
#include "sha2.h"
#include "sockutil.h"

typedef struct ServerState {
  struct tls_config* config;
  struct tls* context;
  socklen_t sock;
  sqlite3* db;
} ServerState;

void ServerState_initialise(ServerState* state);

void ServerState_destroy(ServerState* state);

void ServerState_listenOnce(ServerState* state);
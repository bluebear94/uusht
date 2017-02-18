#include <stdio.h>
#include <sys/socket.h>
#include <tls.h>
#include <sqlite3.h>
#include "serverstate.h"

// Uruwi's Unsurprising Speedy Hellish Textboard, or UUSHT

int main(void /*int argc, char* argv[argc + 1]*/) {
  int stat = tls_init();
  if (stat != 0) {
    fprintf(stderr, "Could not initialise LibreSSL.\n");
    return -1;
  }
  sqlite3_config(SQLITE_CONFIG_SERIALIZED);
  sqlite3_initialize();
  ServerState server = {0};
  ServerState_initialise(&server);
  ServerState_destroy(&server);
  sqlite3_shutdown();
  return 0;
}
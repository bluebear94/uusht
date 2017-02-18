#include <stdio.h>
#include <sys/socket.h>
#include <tls.h>
#include "serverstate.h"

// Uruwi's Unsurprising Speedy Hellish Textboard, or UUSHT

int main(void /*int argc, char* argv[argc + 1]*/) {
  int stat = tls_init();
  if (stat != 0) {
    fprintf(stderr, "Could not initialise LibreSSL.\n");
    return -1;
  }
  ServerState server = {0};
  ServerState_initialise(&server);
  ServerState_destroy(&server);
  return 0;
}
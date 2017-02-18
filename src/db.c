#include "db.h"

int stepBlock(sqlite3_stmt* statement, sqlite3* connection) {
  volatile int stat;
  while ((stat = sqlite3_step(statement)) == SQLITE_BUSY) {
    if (stat != SQLITE_BUSY && stat != SQLITE_DONE && stat != SQLITE_ROW) {
      fprintf(stderr, "SQLite3 error: %s\n", sqlite3_errmsg(connection));
    }
  }
  return stat;
}
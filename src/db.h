#pragma once

#include <stdio.h>
#include <sqlite3.h>

int stepBlock(sqlite3_stmt* statement, sqlite3* connection);
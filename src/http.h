#pragma once

#include <stddef.h>
#include "sockutil.h"

typedef enum ReqType {
  RE_INVALID = -1,
  RE_GET,
  RE_POST,
} ReqType;

ReqType getRequestAddress(char* request, char** thing, size_t* len);

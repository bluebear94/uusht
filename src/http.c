#include "http.h"

#include <string.h>

ReqType getRequestAddress(char* request, char** thing, size_t* len) {
  char* start = strchr(request, ' ');
  if (start == NULL) return RE_INVALID;
  ++start;
  if (*start == '/') ++start;
  size_t length = strcspn(start, " \r") + 1;
  char* end = start + length;
  *end = '\0';
  *len = length;
  *thing = start;
  switch (request[0]) {
    case 'G': return RE_GET;
    case 'P': return RE_POST;
  }
  return RE_INVALID;
}
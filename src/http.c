#include "http.h"

#include <stdlib.h>
#include <string.h>
#include "strutil.h"

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

void sayOK(struct tls* context) {
  tlsWriteMany(context, (const void*) "HTTP 1.1 200 OK\r\n", 17);
}

static const char CTENC[] =
  "Content-Type: text/html; charset=UTF-8\r\n"
  "Content-Encoding: UTF-8\r\n";

void sayContentTypeAndEncoding(struct tls* context) {
  tlsWriteMany(context, (const void*) CTENC, sizeof(CTENC) / sizeof(CTENC[0]) - 1);
}

static const char ARCT[] =
  "Accept-Ranges: bytes\r\n"
  "Connection: close";

void sayAcceptRangeAndConnectionType(struct tls* context) {
  tlsWriteMany(context, (const void*) ARCT, sizeof(ARCT) / sizeof(ARCT[0]) - 1);
}

void sayContentLength(struct tls* context, size_t length) {
  tlsWriteMany(context, (const void*) "Content-Length: ", 16);
  char buffer[20];
  size_t written = stringify10_size_t(buffer, length);
  tlsWriteMany(context, buffer, written);
  tlsWriteMany(context, (const void*) "\r\n", 2);
}

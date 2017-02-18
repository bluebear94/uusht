#pragma once

#include <stddef.h>
#include <tls.h>
#include "sockutil.h"

typedef enum ReqType {
  RE_INVALID = -1,
  RE_GET,
  RE_POST,
} ReqType;

ReqType getRequestAddress(char* request, char** thing, size_t* len);

void sayOK(struct tls* context);
void sayContentTypeAndEncoding(struct tls* context);
void sayAcceptRangeAndConnectionType(struct tls* context);
void sayContentLength(struct tls* context, size_t length);

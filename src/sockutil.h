#pragma once

#include <tls.h>

void tlsReadMany(struct tls* context, void** buf, size_t* l);
void tlsWriteMany(struct tls* context, const void* buffer, size_t len);
void tlsWriteString(struct tls* context, const char* string);
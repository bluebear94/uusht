#pragma once

#include <stddef.h>

#define DECL_STRINGIFY10(type) \
  size_t stringify10_##type(char* buffer, type value)

DECL_STRINGIFY10(size_t);
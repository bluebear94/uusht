#include "strutil.h"

#include <string.h>

static const char DIGITS[] =
  "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";

#define NCCODEa0 \
  int isneg = value < 0; \
  if (isneg) value = -value;
#define NCCODEa1
#define NCCODEb0 \
  if (isneg) *(start--) = '-';
#define NCCODEb1

#define NCCODEa(unsigned) NCCODEa##unsigned
#define NCCODEb(unsigned) NCCODEb##unsigned

#define DEF_STRINGIFY10(type, unsigned) \
  size_t stringify10_##type(char* buffer, type value) { \
    size_t buflen = 3 * sizeof(value) + 1; \
    char temp[buflen]; \
    char* end = temp + buflen; \
    char* start = end - 1; \
    NCCODEa(unsigned) \
    do { \
      if (value < 10) { \
        *start = '0' + (value % 10); \
        --start; \
        break; \
      } else { \
        int rem = value % 100; \
        start[0] = DIGITS[(rem << 1) + 1]; \
        start[-1] = DIGITS[rem << 1]; \
        value /= 100; \
        start -= 2; \
      } \
    } while (value != 0); \
    NCCODEb(unsigned) \
    ++start; \
    memcpy(buffer, start, end - start); \
    return end - start; \
  } \

DEF_STRINGIFY10(size_t, 1)
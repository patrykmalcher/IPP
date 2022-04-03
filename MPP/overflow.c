#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "overflow.h"

bool sizeMaxMultiplicationOverflow(size_t x, size_t y) {
  return x > (size_t) SIZE_MAX / y;
}
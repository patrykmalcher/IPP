#include "error.h"

void printError(size_t digit) {
  fprintf(stderr, "ERROR %zu\n", digit);
}
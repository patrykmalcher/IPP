#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "safeMemory.h"

bool safeMalloc(size_t **ptr, size_t size) {
  *ptr = malloc(size);
  return *ptr == NULL; 
}

bool safeRealloc(size_t **ptr, size_t size) {
  size_t *tmp = realloc(*ptr, size);
  
  if (tmp == NULL) {
    free(*ptr);
    return true;
  }

  *ptr = tmp;
  return false;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bitset.h"

uint8_t *bitsetIni(size_t size) {
  uint8_t *bitset = (uint8_t*) calloc((size + 7) / 8, 1);

  return bitset;
}

void changeIthBit(uint8_t **bitset, size_t i) {
  size_t unit = i / 8;
  i %= 8;

  (*bitset)[unit] |= (uint8_t) 1 << i;
}

bool getIthBit(uint8_t **bitset, size_t i) {
  size_t unit = i / 8;
  i %= 8;

  return (((*bitset)[unit] >> i) & 1) == 1; 
}
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>
#include "scan.h"
#include "overflow.h"
#include "safeMemory.h"
#include "bitset.h"

size_t scanDimensions(size_t **array, size_t *next) {
  char *inBuffer = NULL;
  size_t inBufferSize = 0, size = 1, product = 1;
  char *begin, *end = NULL;

  long long check = getline(&inBuffer, &inBufferSize, stdin);

  if (check == -1) {
    free(inBuffer);
    return 1;
  }

  for (int i = 0; i < check; i++)
    if (!isspace(inBuffer[i]) && !isdigit(inBuffer[i])) {
      free(inBuffer);
      return 1;
    }

  begin = inBuffer;

  size_t number = strtoull(begin, &end, 10);

  while (begin != end) {
    if (sizeMaxMultiplicationOverflow(product, number)) {
      free(inBuffer);
      return 2;
    }

    if (number == 0 || errno == ERANGE) {
      free(inBuffer);
      return 1;
    }

    if ((*next) >= size) {
      size *= 2;

      if (safeRealloc(array, size * sizeof(size_t))) {
        free(inBuffer);
        return 2;
      }
    }

    product *= number;
    (*array)[(*next)] = product;
    (*next) ++;

    begin = end;
    number = strtoull(begin, &end, 10);
  }

  free(inBuffer);

  if((*next) == 1)
    return 1;

  return 0;
}

bool scanPoint(size_t *point, size_t k, size_t **productsOfDimensions) {
  char *inBuffer = NULL;
  size_t inBufferSize = 0, next = 0;
  char *begin, *end = NULL;

  long long check = getline(&inBuffer, &inBufferSize, stdin);

  if (check == -1) {
    free(inBuffer);
    return 1;
  }

  for (int i = 0; i < check; i++)
    if (!isspace(inBuffer[i]) && !isdigit(inBuffer[i])) {
      free(inBuffer);
      return 1;
    }

  begin = inBuffer;

  size_t number = strtoull(begin, &end, 10);

  while (begin != end) {
    if (next == k) {
      free(inBuffer);
      return 1;
    }

    if (number == 0 || errno == ERANGE || number > (*productsOfDimensions)[next + 1] / (*productsOfDimensions)[next]) {
      free(inBuffer);
      return 1;
    }

    *point += (*productsOfDimensions)[next] * (number - 1);
    next ++;

    begin = end;
    number = strtoull(begin, &end, 10);
  }

  if (next != k) {
    free(inBuffer);
    return 1;
  }

  free(inBuffer);
  return 0;
}

// Zamienia cyfrę w postaci szesnastkowej na liczbę dziesiętną.
static size_t convert(char c) {
  if (c >= '0' && c <= '9')
    return (size_t) c - '0';
  
  if (c >= 'a' && c <= 'f')
    return (size_t) c - 'a' + 10;
  
  if (c >= 'A' && c <= 'F')
    return (size_t) c - 'A' + 10;

  return 0;
}

// Rozpatruje liczbę opisującą labirynt w postaci szesnastkowej.
static bool hexNumber(char **inBuffer, uint8_t **vis, size_t begin, size_t end, size_t sizeOfMaze) {
  for (long long j = end - 1; j >= (long long) begin; j--) {
    size_t digit = convert((*inBuffer)[j]);

  for (int k = 0; k < 4; k++)
    if ((digit >> k) & 1) {
      if ((end - j - 1) * 4 + k >= sizeOfMaze) {
        free(*inBuffer);
        return 1;
      }

      changeIthBit(vis, (end - j - 1) * 4 + k);
    }
  }

  free(*inBuffer);
  return 0;
}

// Rozpatruje liczbę opisującą labirynt w postaci "R".
static bool rNumber(char **inBuffer, char **newPtr, uint8_t ** vis, size_t sizeOfMaze) {
  char *begin, *end = NULL;
  size_t a = 0, b = 0, m = 0, r = 0, s0 = 0, i = 0;

  begin = *newPtr;

  size_t number = strtoull(begin, &end, 10);

  while(begin != end) {
    if (number > (size_t) UINT32_MAX) {
      free(*inBuffer);
      return 1;
    }

    if (i == 0)
      a = number;

    if (i == 1)
      b = number;

    if (i == 2)
      m = number;

    if (i == 3)
      r = number;

    if (i == 4)
      s0 = number;

    i ++;
    begin = end;
    number = strtoull(begin, &end, 10);
  }

  if (i != 5 || m == 0) {
    free(*inBuffer);
    return 1;
  }

  for (size_t j = 1; j <= r; j++) {
    s0 = (a * s0 % m + b % m) % m;

    size_t w = s0 % sizeOfMaze;

    if (w < (size_t) 1 << 32)
      for (size_t k = w; k < sizeOfMaze; k += (size_t) 1 << 32)
        changeIthBit(vis, k);
  }

  free(*inBuffer);
  return 0;
}

bool scanMaze(uint8_t **vis, size_t sizeOfMaze) {
  char *inBuffer = NULL;
  size_t inBufferSize = 0;

  long long check = getline(&inBuffer, &inBufferSize, stdin);

  if (check == -1) {
    free(inBuffer);
    return 1;
  }

  for(int i = 0; i < check; i++) {
    if (!isspace(inBuffer[i]) && inBuffer[i] != 'R' && inBuffer[i] != '0') {
      free(inBuffer);
      return 1;
    }

    if (inBuffer[i] == 'R') {
      for (int j = i + 1; j < check; j++)
        if (!isspace(inBuffer[j]) && !isdigit(inBuffer[j])) {
          free(inBuffer);
          return 1;
        } 

      char *newPtr = inBuffer + i + 1;
      
      return rNumber(&inBuffer, &newPtr, vis, sizeOfMaze);
    }

    if (inBuffer[i] == '0') {
      if (i + 2 >= check || inBuffer[i + 1] != 'x' || !isxdigit(inBuffer[i + 2])) {
        free (inBuffer);
        return 1;
      }

      bool wasWhiteSpace = false;

      size_t end = check;

      for (int j = i + 2; j < check; j++) 
        if (!isxdigit(inBuffer[j]) && !isspace(inBuffer[j])) {
          free (inBuffer);
          return 1;
        }
        else if (isspace(inBuffer[j])) {
          if (!wasWhiteSpace)
            end = j;

          wasWhiteSpace = true;
        }
        else if (wasWhiteSpace) {
          free(inBuffer);
          return 1;
        }
      
      return hexNumber(&inBuffer, vis, i + 2, end, sizeOfMaze);
    }
  }

  free(inBuffer);
  return 1;
}
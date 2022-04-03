#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "scan.h"
#include "safeMemory.h"
#include "error.h"
#include "bitset.h"
#include "bfs.h"

int main() {
  size_t *productsOfDimensions;
  size_t dimension = 1;

  if (safeMalloc(&productsOfDimensions, sizeof(size_t))) {
    printError(0);
    return 1;
  }

  productsOfDimensions[0] = 1;

  long long check = scanDimensions(&productsOfDimensions, &dimension);

  dimension --;

  if (check == 2) {
    free(productsOfDimensions);
    printError(0);
    return 1;
  }

  if (check == 1) {
    free(productsOfDimensions);
    printError(1);
    return 0;
  }

  size_t startPoint = 0, endPoint = 0;

  check = scanPoint(&startPoint, dimension, &productsOfDimensions);

  if (check == 1) {
    free(productsOfDimensions);
    printError(2);
    return 0;
  }

  check = scanPoint(&endPoint, dimension, &productsOfDimensions);

  if (check == 1) {
    free(productsOfDimensions);
    printError(3);
    return 0;
  }

  uint8_t *vis = bitsetIni(productsOfDimensions[dimension]);

  if (vis == NULL) {
    free(productsOfDimensions);
    free(vis);
    printError(0);
    return 1;
  }

  check = scanMaze(&vis, productsOfDimensions[dimension]);

  if (getIthBit(&vis, startPoint)) {
    free(productsOfDimensions);
    free(vis);
    printError(2);
    return 0;
  }

  if (getIthBit(&vis, endPoint)) {
    free(productsOfDimensions);
    free(vis);
    printError(3);
    return 0;
  }

  if (check == 1) {
    free(productsOfDimensions);
    free(vis);
    printError(4);
    return 0;
  }

  int c = getchar();

  if (c != EOF) {
    free(productsOfDimensions);
    free(vis);
    printError(5);
    return 0;
  }

  check = bfs(startPoint, endPoint, &productsOfDimensions, &vis, dimension);

  if (check == -1) {
    free(productsOfDimensions);
    free(vis);
    printError(0);
    return 1;
  }

  if (check == -2) {
    free(productsOfDimensions);
    free(vis);
    printf("NO WAY\n");
    return 0;
  }

  printf("%zu\n", (size_t) check);

  free(productsOfDimensions);
  free(vis);

  return 0;
}
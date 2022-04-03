#include <stdio.h>
#include <stdint.h>
#include "bfs.h"
#include "bitset.h"
#include "queue.h"

long long bfs(size_t startPoint, size_t endPoint, size_t **productsOfDimension, uint8_t **vis, size_t dimension) {
  if (startPoint == endPoint)
    return 0;

  long long dist = 0;

  // Sprytny sposób na ograniczenie pamięci. Dwie zmienne symbolizujące ilość pozostałych do przetworzenia wierzchołków
  // na aktualnej i następnej warstwie (warstwa = grupa wierzchołków o danej odległości od wierzchołka startowego).
  // Dzięki temu wiemy, kiedy zwiększyć odległość przez co nie trzeba stosować 2bitbfsa, ani trzymać odległości na kolejce. 
  size_t amountAtCurrentLayer = 1, amountAtNextLayer = 0;

  struct Queue *q = initQueue();
  
  if (q == NULL) {
    QClear(q);
    return -1;
  }

  bool check = QPush(q, startPoint);

  if (check) {
    QClear(q);
    return -1;
  }

  while (!QEmpty(q)) {
    size_t f = QFront(q);

    for (size_t i = 0; i < dimension; i++) {
      if (f % (*productsOfDimension)[i + 1] >= (*productsOfDimension)[i]) {
        size_t next = f - (*productsOfDimension)[i];

        if (!getIthBit(vis, next)) {
          if (next == endPoint) {
            QClear(q);
            return dist + 1;
          }

          check = QPush(q, next);

          if (check) {
            QClear(q);
            return -1;
          }

          changeIthBit(vis, next);

          amountAtNextLayer ++;
        }
      }

      if (f % (*productsOfDimension)[i + 1] < (*productsOfDimension)[i + 1] - (*productsOfDimension)[i]) {
        size_t next = f + (*productsOfDimension)[i];

        if (!getIthBit(vis, next)) {
          if (next == endPoint) {
            QClear(q);
            return dist + 1;
          }

          check = QPush(q, next);

          if (check) {
            QClear(q);
            return -1;
          }

          changeIthBit(vis, next);

          amountAtNextLayer ++;
        }
      }
    }
    
    QPop(q);

    amountAtCurrentLayer --;

    if (amountAtCurrentLayer == 0) {
      amountAtCurrentLayer = amountAtNextLayer;
      amountAtNextLayer = 0;
      dist ++;
    }
  }

  QClear(q);
  
  return -2;
}
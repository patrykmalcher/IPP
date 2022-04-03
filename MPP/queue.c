#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"

struct QNode *newNode(size_t k) {
  struct QNode *newNode = malloc(sizeof(struct QNode));

  if (newNode == NULL)
    return NULL;

  newNode->key = k;
  newNode->next = NULL;

  return newNode;
}

struct Queue *initQueue() {
  struct Queue *newQueue = malloc(sizeof(struct Queue));
  
  if (newQueue == NULL)
    return NULL;

  newQueue->first = newQueue->last = NULL;

  return newQueue;
}

bool QPush(struct Queue *q, size_t k) {
  struct QNode *tmp = newNode(k);

  if (tmp == NULL)
    return 1;

  if (q->last == NULL) {
    q->first = q->last = tmp;
  }
  else {
    q->last->next = tmp, q->last = tmp;
  }

  return 0;
}

void QPop(struct Queue *q) {
  struct QNode *tmp = q->first;
  q->first = q->first->next;

  if (q->first == NULL)
    q->last = NULL;

  free(tmp);
}

bool QEmpty(struct Queue *q) {
  return q->first == NULL;
}

size_t QFront(struct Queue *q) {
  return q->first->key;
}

void QClear(struct Queue *q) {
  while (!QEmpty(q))
    QPop(q);
  free(q);
}
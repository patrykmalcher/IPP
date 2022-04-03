// Moduł z kolejką wykorzystywaną do algorytmu BFS.
#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>

// Definicja elementu kolejki.
struct QNode {
  size_t key;
  struct QNode *next;
};

// Definicja kolejki.
struct Queue {
  struct QNode *first, *last;
};

// Tworzy i zwraca wskaźnik do nowego elementu kolejki lub NULL przy błędzie alokacji pamięci.
struct QNode *newNode(size_t k);

// Tworzy i zwraca wskaźnik do nowej kolejki lub NULL przy błędzie alokacji pamięci.
struct Queue *initQueue();

// Dodaje nowy element z kluczem k do kolejki. Zwraca 1 przy błędzie alokacji pamięci lub 0, jeśli wszystko pójdzie pomyślnie.
bool QPush(struct Queue *q, size_t k);

// Usuwa pierwszy element z kolejki i zwalnia pamięć mu przypisaną.
void QPop(struct Queue *q);

// Zwraca prawdę, jeśli kolejka jest pusta lub fałsz w przeciwnym przypadku.
bool QEmpty(struct Queue *g);

// Zwraca klucz pierwszego elementu kolejki.
size_t QFront(struct Queue *q);

// Czyści i zwalnia pamięć przeznaczoną na kolejkę.
void QClear(struct Queue *q);

#endif
// Moduł mający na celu obsługę błędów alokacji pamięci.
#ifndef SAFEMEMORY_H
#define SAFEMEMORY_H

#include <stdio.h>
#include <stdbool.h>

// Alokuje pamięć. Zwraca 1 w przypadku błędu alokacji lub 0 w przeciwnym przypadku.
bool safeMalloc(size_t **ptr, size_t size);

// Realokuje pamięć. Zwraca 1 w przypadku błędu realokacji lub 0 w przeciwnym przypadku.
bool safeRealloc(size_t **ptr, size_t size);

#endif
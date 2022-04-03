// Moduł z algorytmem BFS, głównym rozwiązaniem problemu.
#ifndef BFS_H
#define BFS_H

#include <stdio.h>
#include <stdint.h>

// Zwraca -1 przy błędzie alokacji pamięci, -2 jeśli nie ma szukanej ścieżki lub długość ścieżki w przeciwnym przypadku.
long long bfs(size_t startPoint, size_t endPoint, size_t **productsofDimension, uint8_t **vis, size_t dimension);

#endif
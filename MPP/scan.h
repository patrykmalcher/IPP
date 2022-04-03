// Moduł mający na celu wczytanie danych.
#ifndef SCAN_H
#define SCAN_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Wczytuje wymiary labiryntu, zamieniając je na iloczyny kolejnych wymiarów. 
// Zwraca 1 przy błędnych danych, 2 przy błędzie alokacji pamięci lub 0 w przeciwnym przypadku.
size_t scanDimensions(size_t **array, size_t *i);

// Wczytuje punkt (zarówno początkowy jak i końcowy).
// Zwraca 1 przy błędnych danych lub 0 w przeciwnym przypadku.
bool scanPoint(size_t *point, size_t k, size_t **productsOfDimensions);

// Wczytuje liczbę opisującą labirynt.
// Zwraca 1 przy błędnych danych lub 0 w przeciwnym przypadku.
bool scanMaze(uint8_t **vis, size_t sizeOfMaze);

#endif
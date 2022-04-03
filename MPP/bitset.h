// Moduł, który pomaga w ograniczeniu pamięci i wykorzystaniu
// w pełni każdego zaalokowanego bita. Dostarcza tablicę bitów
// (bitseta).
#ifndef BITSET_H
#define BITSET_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Inicjalizuje bitseta. Zwraca wskaźnik
// do nowo przydzielonej pamięci lub NULL
// w przypadku błędu alokacji.
uint8_t *bitsetIni(size_t size);

// Zmienia i-ty bit w bitsecie.
void changeIthBit(uint8_t **bitset, size_t i);

// zwraca i-ty bit w bitsecie.
bool getIthBit(uint8_t **bitset, size_t i);

#endif

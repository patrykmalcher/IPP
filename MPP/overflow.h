// Moduł mający na celu bezpieczną obsługę arytmetyki liczb.
#ifndef OVERFLOW_H
#define OVERFLOW_H

#include <stdio.h>
#include <stdbool.h>

// Zwraca prawdę, jeśli iloczyn x i y przekracza SIZE_MAX lub fałsz w przeciwnym przypadku.
bool sizeMaxMultiplicationOverflow(size_t x, size_t y);

#endif
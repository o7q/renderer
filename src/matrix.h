#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

bool matrix_in_range(int y, int x, int height, int width);
int matrix_get_1d_index(int y, int x, int width);

#endif
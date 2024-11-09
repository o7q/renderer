#include "matrix.h"

bool matrix_in_range(int y, int x, int height, int width)
{
    return y < height && y >= 0 && x < width && x >= 0;
}

int matrix_get_1d_index(int y, int x, int width)
{
    return y * width + x;
}
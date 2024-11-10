#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool mat2_in_range(const struct Mat2 *matrix, size_t y, size_t x, size_t height, size_t width)
{
    // not checking <= 0 values because size_t is always positive
    return matrix && y < height && x < width;
}

static size_t mat2_index(size_t y, size_t x, size_t width)
{
    return y * width + x;
}

struct Mat2 *mat2_create(size_t height, size_t width, enum Mat2_Type type)
{
    if (height <= 0 || width <= 0)
    {
        return NULL;
    }

    struct Mat2 *matrix = malloc(sizeof(struct Mat2));

    if (!matrix)
    {
        return NULL;
    }

    matrix->type = type;

    matrix->height = height;
    matrix->width = width;
    matrix->area = height * width;

    matrix->data = NULL;

    size_t size = 0;

    switch (matrix->type)
    {
    case MAT2_FLOAT:
        size = sizeof(float);
        break;
    case MAT2_CHAR:
        size = sizeof(char);
        break;
    default:
        break;
    }

    if (size == 0)
    {
        return NULL;
    }

    matrix->data = calloc(height * width, size);

    if (!matrix->data)
    {
        free(matrix);
        return NULL;
    }

    return matrix;
}

void mat2_delete(struct Mat2 *matrix)
{
    if (matrix)
    {
        if (matrix->data)
        {
            free(matrix->data);
        }
        free(matrix);
    }
}

void mat2_write_float(struct Mat2 *matrix, size_t y, size_t x, float value)
{
    if (!mat2_in_range(matrix, y, x, matrix->height, matrix->width) || matrix->type != MAT2_FLOAT)
    {
        return;
    }
    ((float *)matrix->data)[mat2_index(y, x, matrix->width)] = value;
}

float mat2_read_float(struct Mat2 *matrix, size_t y, size_t x)
{
    if (!mat2_in_range(matrix, y, x, matrix->height, matrix->width) || matrix->type != MAT2_FLOAT)
    {
        return 0.0f;
    }
    return ((float *)matrix->data)[mat2_index(y, x, matrix->width)];
}

void mat2_write_char(struct Mat2 *matrix, size_t y, size_t x, char value)
{
    if (!mat2_in_range(matrix, y, x, matrix->height, matrix->width) || matrix->type != MAT2_CHAR)
    {
        return;
    }
    ((char *)matrix->data)[mat2_index(y, x, matrix->width)] = value;
}

char mat2_read_char(struct Mat2 *matrix, size_t y, size_t x)
{
    if (!mat2_in_range(matrix, y, x, matrix->height, matrix->width) || matrix->type != MAT2_CHAR)
    {
        return '\0';
    }
    return ((char *)matrix->data)[mat2_index(y, x, matrix->width)];
}
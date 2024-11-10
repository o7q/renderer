#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

#include "geometry/geometry.h"

enum Mat2_Type
{
    MAT2_FLOAT,
    MAT2_CHAR
};

struct Mat2
{
    enum Mat2_Type type;

    size_t height;
    size_t width;

    size_t area;

    void *data;
};

struct Mat2 *mat2_create(size_t height, size_t width, enum Mat2_Type type);
void mat2_delete(struct Mat2 *matrix);
void mat2_write_float(struct Mat2 *matrix, size_t y, size_t x, float value);
float mat2_read_float(struct Mat2 *matrix, size_t y, size_t x);

void mat2_write_char(struct Mat2 *matrix, size_t y, size_t x, char value);
char mat2_read_char(struct Mat2 *matrix, size_t y, size_t x);

void vec3_multiply_mat2_4x4(struct Mat2 *matrix, struct Vec3 i_vec, struct Vec3 *i_vec2);

#endif
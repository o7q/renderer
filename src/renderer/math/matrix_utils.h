#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include "geometry/types.h"
#include "matrix.h"

struct Vec3 matrix_multiply_vector_4x4(struct Mat2 *m, struct Vec3 *v);
struct Mat2 *matrix_multiply_matrix_4x4(struct Mat2 *a, struct Mat2 *b);

struct Mat2 *matrix_create_projection(float fov, float aspect, float clip_near, float clip_far);
struct Mat2 *matrix_create_translation(struct Vec3 *v);
struct Mat2 *matrix_create_x_rotation(float x_rot);
struct Mat2 *matrix_create_y_rotation(float y_rot);
struct Mat2 *matrix_create_z_rotation(float z_rot);

#endif
#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"
#include "geometry/types.h"

struct Vec3 vec3_add(struct Vec3 *vec_a, struct Vec3 *vec_b);
struct Vec3 vec3_add_float(struct Vec3 *vec_a, float f_a);

struct Vec3 vec3_subtract(struct Vec3 *vec_a, struct Vec3 *vec_b);
struct Vec3 vec3_subtract_float(struct Vec3 *vec_a, float f_a);

struct Vec3 vec3_multiply(struct Vec3 *vec_a, struct Vec3 *vec_b);
struct Vec3 vec3_multiply_float(struct Vec3 *vec_a, float f_a);

struct Vec3 vec3_divide(struct Vec3 *vec_a, struct Vec3 *vec_b);
struct Vec3 vec3_divide_float(struct Vec3 *vec_a, float f_a);

float vec3_dot(struct Vec3 *vec_a, struct Vec3 *vec_b);
struct Vec3 vec3_cross(struct Vec3 *vec_a, struct Vec3 *vec_b);
float vec3_length(struct Vec3 *vec_a);
struct Vec3 vec3_normalize(struct Vec3 *vec_a);

#endif
#include "vector.h"

#include <math.h>

struct Vec3 vec3_add(struct Vec3 *vec_a, struct Vec3 *vec_b)
{
    return (struct Vec3){vec_a->x + vec_b->x, vec_a->y + vec_b->y, vec_a->z + vec_b->z, vec_a->w};
}
struct Vec3 vec3_add_float(struct Vec3 *vec_a, float f_a)
{
    return (struct Vec3){vec_a->x + f_a, vec_a->y + f_a, vec_a->z + f_a, vec_a->w};
}

struct Vec3 vec3_subtract(struct Vec3 *vec_a, struct Vec3 *vec_b)
{
    return (struct Vec3){vec_a->x - vec_b->x, vec_a->y - vec_b->y, vec_a->z - vec_b->z, vec_a->w};
}
struct Vec3 vec3_subtract_float(struct Vec3 *vec_a, float f_a)
{
    return (struct Vec3){vec_a->x - f_a, vec_a->y - f_a, vec_a->z - f_a, vec_a->w};
}

struct Vec3 vec3_multiply(struct Vec3 *vec_a, struct Vec3 *vec_b)
{
    return (struct Vec3){vec_a->x * vec_b->x, vec_a->y * vec_b->y, vec_a->z * vec_b->z, vec_a->w};
}
struct Vec3 vec3_multiply_float(struct Vec3 *vec_a, float f_a)
{
    return (struct Vec3){vec_a->x * f_a, vec_a->y * f_a, vec_a->z * f_a, vec_a->w};
}

struct Vec3 vec3_divide(struct Vec3 *vec_a, struct Vec3 *vec_b)
{
    return (struct Vec3){vec_a->x / vec_b->x, vec_a->y / vec_b->y, vec_a->z / vec_b->z, vec_a->w};
}
struct Vec3 vec3_divide_float(struct Vec3 *vec_a, float f_a)
{
    return (struct Vec3){vec_a->x / f_a, vec_a->y / f_a, vec_a->z / f_a, vec_a->w};
}

float vec3_dot(struct Vec3 *vec_a, struct Vec3 *vec_b)
{
    return vec_a->x * vec_b->x + vec_a->y * vec_b->y + vec_a->z * vec_b->z;
}

struct Vec3 vec3_cross(struct Vec3 *vec_a, struct Vec3 *vec_b)
{
    // cross product
    return (struct Vec3){vec_a->y * vec_b->z - vec_a->z * vec_b->y,
                         vec_a->z * vec_b->x - vec_a->x * vec_b->z,
                         vec_a->x * vec_b->y - vec_a->y * vec_b->x,
                         vec_a->w};
}

float vec3_length(struct Vec3 *vec_a)
{
    // vec3_dot is squared distance of the vector, so take the square root
    return sqrtf(vec3_dot(vec_a, vec_a));
}

struct Vec3 vec3_normalize(struct Vec3 *vec_a)
{
    // divide each element of the vector by its length
    return vec3_divide_float(vec_a, vec3_length(vec_a));
}
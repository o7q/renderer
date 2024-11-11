#include "vector.h"

#include <math.h>

struct Vec3 vec3_add(struct Vec3 *a, struct Vec3 *b)
{
    return (struct Vec3){a->x + b->x, a->y + b->y, a->z + b->z};
}
struct Vec3 vec3_add_float(struct Vec3 *a, float f)
{
    return (struct Vec3){a->x + f, a->y + f, a->z + f};
}

struct Vec3 vec3_subtract(struct Vec3 *a, struct Vec3 *b)
{
    return (struct Vec3){a->x - b->x, a->y - b->y, a->z - b->z};
}
struct Vec3 vec3_subtract_float(struct Vec3 *a, float f)
{
    return (struct Vec3){a->x - f, a->y - f, a->z - f};
}

struct Vec3 vec3_multiply(struct Vec3 *a, struct Vec3 *b)
{
    return (struct Vec3){a->x * b->x, a->y * b->y, a->z * b->z};
}
struct Vec3 vec3_multiply_float(struct Vec3 *a, float f)
{
    return (struct Vec3){a->x * f, a->y * f, a->z * f};
}

struct Vec3 vec3_divide(struct Vec3 *a, struct Vec3 *b)
{
    return (struct Vec3){a->x / b->x, a->y / b->y, a->z / b->z};
}
struct Vec3 vec3_divide_float(struct Vec3 *a, float f)
{
    return (struct Vec3){a->x / f, a->y / f, a->z / f};
}

float vec3_dot(struct Vec3 *a, struct Vec3 *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

struct Vec3 vec3_cross(struct Vec3 *a, struct Vec3 *b)
{
    return (struct Vec3){a->y * b->z - a->z * b->y,
                         a->z * b->x - a->x * b->z,
                         a->x * b->y - a->y * b->x};
}

float vec3_length(struct Vec3 *a)
{
    return sqrtf(vec3_dot(a, a));
}

struct Vec3 vec3_normalize(struct Vec3 *a)
{
    return vec3_divide_float(a, vec3_length(a));
}
#include "matrix_math.h"

#include "matrix.h"

struct Vec3 matrix_multiply_vector_4x4(struct Mat2 *m, struct Vec3 *v)
{
    struct Vec3 o_vec;

    o_vec.x = v->x * mat2_read_float(m, 0, 0) +
              v->y * mat2_read_float(m, 1, 0) +
              v->z * mat2_read_float(m, 2, 0) +
              mat2_read_float(m, 3, 0);

    o_vec.y = v->x * mat2_read_float(m, 0, 1) +
              v->y * mat2_read_float(m, 1, 1) +
              v->z * mat2_read_float(m, 2, 1) +
              mat2_read_float(m, 3, 1);

    o_vec.z = v->x * mat2_read_float(m, 0, 2) +
              v->y * mat2_read_float(m, 1, 2) +
              v->z * mat2_read_float(m, 2, 2) +
              mat2_read_float(m, 3, 2);

    float w = v->x * mat2_read_float(m, 0, 3) +
              v->y * mat2_read_float(m, 1, 3) +
              v->z * mat2_read_float(m, 2, 3) +
              mat2_read_float(m, 3, 3);

    if (w != 0)
    {
        o_vec.x /= w;
        o_vec.y /= w;
        o_vec.z /= w;
    }

    return o_vec;
}

struct Mat2 *matrix_multiply_matrix_4x4(struct Mat2 *a, struct Mat2 *b)
{
    struct Mat2 *matrix = mat2_create(4, 4, MAT2_FLOAT);

    for (int c = 0; c < 4; c++)
    {
        for (int r = 0; r < 4; r++)
        {
            float value = mat2_read_float(a, r, 0) * mat2_read_float(b, 0, c) +
                          mat2_read_float(a, r, 1) * mat2_read_float(b, 1, c) +
                          mat2_read_float(a, r, 2) * mat2_read_float(b, 2, c) +
                          mat2_read_float(a, r, 3) * mat2_read_float(b, 3, c);
            mat2_write_float(matrix, r, c, value);
        }
    }

    return matrix;
}
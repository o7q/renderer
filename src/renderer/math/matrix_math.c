#include "matrix.h"

#include "geometry/geometry.h"

struct Vec3 vec3_multiply_mat2_4x4(struct Mat2 *matrix, struct Vec3 i_vec)
{
    struct Vec3 o_vec;

    o_vec.x = i_vec.x * mat2_read_float(matrix, 0, 0) +
              i_vec.y * mat2_read_float(matrix, 1, 0) +
              i_vec.z * mat2_read_float(matrix, 2, 0) +
              mat2_read_float(matrix, 3, 0);

    o_vec.y = i_vec.x * mat2_read_float(matrix, 0, 1) +
              i_vec.y * mat2_read_float(matrix, 1, 1) +
              i_vec.z * mat2_read_float(matrix, 2, 1) +
              mat2_read_float(matrix, 3, 1);

    o_vec.z = i_vec.x * mat2_read_float(matrix, 0, 2) +
              i_vec.y * mat2_read_float(matrix, 1, 2) +
              i_vec.z * mat2_read_float(matrix, 2, 2) +
              mat2_read_float(matrix, 3, 2);

    float w = i_vec.x * mat2_read_float(matrix, 0, 3) +
              i_vec.y * mat2_read_float(matrix, 1, 3) +
              i_vec.z * mat2_read_float(matrix, 2, 3) +
              mat2_read_float(matrix, 3, 3);

    if (w != 0)
    {
        o_vec.x /= w;
        o_vec.y /= w;
        o_vec.z /= w;
    }

    return o_vec;
}
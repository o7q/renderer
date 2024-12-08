#include "matrix_utils.h"

#include "matrix.h"
#include "vector.h"

struct Vec3 matrix_multiply_vector_4x4(struct Mat2 *mat_a, struct Vec3 *vec_a)
{
    struct Vec3 vec_out;

    vec_out.x = vec_a->x * mat2_read_float(mat_a, 0, 0) +
                vec_a->y * mat2_read_float(mat_a, 1, 0) +
                vec_a->z * mat2_read_float(mat_a, 2, 0) +
                vec_a->w * mat2_read_float(mat_a, 3, 0);

    vec_out.y = vec_a->x * mat2_read_float(mat_a, 0, 1) +
                vec_a->y * mat2_read_float(mat_a, 1, 1) +
                vec_a->z * mat2_read_float(mat_a, 2, 1) +
                vec_a->w * mat2_read_float(mat_a, 3, 1);

    vec_out.z = vec_a->x * mat2_read_float(mat_a, 0, 2) +
                vec_a->y * mat2_read_float(mat_a, 1, 2) +
                vec_a->z * mat2_read_float(mat_a, 2, 2) +
                vec_a->w * mat2_read_float(mat_a, 3, 2);

    vec_out.w = vec_a->x * mat2_read_float(mat_a, 0, 3) +
                vec_a->y * mat2_read_float(mat_a, 1, 3) +
                vec_a->z * mat2_read_float(mat_a, 2, 3) +
                vec_a->w * mat2_read_float(mat_a, 3, 3);

    return vec_out;
}

struct Mat2 *matrix_multiply_matrix_4x4(struct Mat2 *mat_a, struct Mat2 *mat_b)
{
    struct Mat2 *mat_mult = mat2_create(4, 4, MAT2_FLOAT);

    for (int c = 0; c < 4; c++)
    {
        for (int r = 0; r < 4; r++)
        {
            float value = mat2_read_float(mat_a, r, 0) * mat2_read_float(mat_b, 0, c) +
                          mat2_read_float(mat_a, r, 1) * mat2_read_float(mat_b, 1, c) +
                          mat2_read_float(mat_a, r, 2) * mat2_read_float(mat_b, 2, c) +
                          mat2_read_float(mat_a, r, 3) * mat2_read_float(mat_b, 3, c);
            mat2_write_float(mat_mult, r, c, value);
        }
    }

    return mat_mult;
}

struct Mat2 *matrix_point_at(struct Vec3 *position, struct Vec *target, struct Vec3 *up)
{
    struct Vec3 new_foward = vec3_subtract(target, position);
    new_foward = vec3_normalize(&new_foward);

    float u_n_dot = vec3_dot(up, &new_foward);
    struct Vec3 a = vec3_multiply_float(&new_foward, u_n_dot);
    struct Vec3 new_up = vec3_subtract(up, &a);
    new_up = vec3_normalize(&new_up);

    struct Vec3 new_right = vec3_cross(&new_up, &new_foward);

    struct Mat2 *point_at_mat = mat2_create(4, 4, MAT2_FLOAT);
    mat2_write_float(point_at_mat, 0, 0, new_right.x);
    mat2_write_float(point_at_mat, 0, 1, new_right.y);
    mat2_write_float(point_at_mat, 0, 2, new_right.z);
    mat2_write_float(point_at_mat, 0, 3, 0.0f);

    mat2_write_float(point_at_mat, 1, 0, new_up.x);
    mat2_write_float(point_at_mat, 1, 1, new_up.y);
    mat2_write_float(point_at_mat, 1, 2, new_up.z);
    mat2_write_float(point_at_mat, 1, 3, 0.0f);

    mat2_write_float(point_at_mat, 2, 0, new_foward.x);
    mat2_write_float(point_at_mat, 2, 1, new_foward.y);
    mat2_write_float(point_at_mat, 2, 2, new_foward.z);
    mat2_write_float(point_at_mat, 2, 3, 0.0f);

    mat2_write_float(point_at_mat, 3, 0, position->x);
    mat2_write_float(point_at_mat, 3, 1, position->y);
    mat2_write_float(point_at_mat, 3, 2, position->z);
    mat2_write_float(point_at_mat, 3, 3, 1.0f);

    return point_at_mat;
}

// matrix.m[0][0] = m.m[0][0];
// matrix.m[0][1] = m.m[1][0];
// matrix.m[0][2] = m.m[2][0];
// matrix.m[0][3] = 0.0f;

// matrix.m[1][0] = m.m[0][1];
// matrix.m[1][1] = m.m[1][1];
// matrix.m[1][2] = m.m[2][1];
// matrix.m[1][3] = 0.0f;

// matrix.m[2][0] = m.m[0][2];
// matrix.m[2][1] = m.m[1][2];
// matrix.m[2][2] = m.m[2][2];
// matrix.m[2][3] = 0.0f;

// matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
// matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
// matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
// matrix.m[3][3] = 1.0f;

struct Mat2 *matrix_quick_inverse(struct Mat2 *mat)
{
    struct Mat2 *inverse_mat = mat2_create(4, 4, MAT2_FLOAT);

    mat2_write_float(inverse_mat, 0, 0, mat2_read_float(mat, 0, 0));
    mat2_write_float(inverse_mat, 0, 1, mat2_read_float(mat, 1, 0));
    mat2_write_float(inverse_mat, 0, 2, mat2_read_float(mat, 2, 0));
    mat2_write_float(inverse_mat, 0, 3, 0.0f);

    mat2_write_float(inverse_mat, 1, 0, mat2_read_float(mat, 0, 1));
    mat2_write_float(inverse_mat, 1, 1, mat2_read_float(mat, 1, 1));
    mat2_write_float(inverse_mat, 1, 2, mat2_read_float(mat, 2, 1));
    mat2_write_float(inverse_mat, 1, 3, 0.0f);

    mat2_write_float(inverse_mat, 2, 0, mat2_read_float(mat, 0, 2));
    mat2_write_float(inverse_mat, 2, 1, mat2_read_float(mat, 1, 2));
    mat2_write_float(inverse_mat, 2, 2, mat2_read_float(mat, 2, 2));
    mat2_write_float(inverse_mat, 2, 3, 0.0f);

    mat2_write_float(inverse_mat, 3, 0, -(mat2_read_float(mat, 3, 0) * mat2_read_float(inverse_mat, 0, 0) + mat2_read_float(mat, 3, 1) * mat2_read_float(inverse_mat, 1, 0) + mat2_read_float(mat, 3, 2) * mat2_read_float(inverse_mat, 2, 0)));
    mat2_write_float(inverse_mat, 3, 1, -(mat2_read_float(mat, 3, 0) * mat2_read_float(inverse_mat, 0, 1) + mat2_read_float(mat, 3, 1) * mat2_read_float(inverse_mat, 1, 1) + mat2_read_float(mat, 3, 2) * mat2_read_float(inverse_mat, 2, 1)));
    mat2_write_float(inverse_mat, 3, 2, -(mat2_read_float(mat, 3, 0) * mat2_read_float(inverse_mat, 0, 2) + mat2_read_float(mat, 3, 1) * mat2_read_float(inverse_mat, 1, 2) + mat2_read_float(mat, 3, 2) * mat2_read_float(inverse_mat, 2, 2)));
    mat2_write_float(inverse_mat, 3, 3, 1.0f);

    return inverse_mat;
}
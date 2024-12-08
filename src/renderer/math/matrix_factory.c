#include "matrix_utils.h"

#include <math.h>

#include "matrix.h"
#include "angle.h"

struct Mat2 *matrix_create_projection(float fov, float aspect, float clip_near, float clip_far)
{
    float fov_radians = 1.0f / tanf(degrees_to_radians(fov / 2.0f));

    struct Mat2 *proj_mat = mat2_create(4, 4, MAT2_FLOAT);

    mat2_write_float(proj_mat, 0, 0, aspect * fov_radians);
    mat2_write_float(proj_mat, 1, 1, fov_radians);
    mat2_write_float(proj_mat, 2, 2, clip_far / (clip_far - clip_near));
    mat2_write_float(proj_mat, 3, 2, (-clip_far * clip_near) / (clip_far - clip_near));
    mat2_write_float(proj_mat, 2, 3, 1.0f);
    mat2_write_float(proj_mat, 3, 3, 0.0f);

    return proj_mat;
}

struct Mat2 *matrix_create_translation(struct Vec3 *v)
{
    struct Mat2 *trans_mat = mat2_create(4, 4, MAT2_FLOAT);

    mat2_write_float(trans_mat, 0, 0, 1.0f);
    mat2_write_float(trans_mat, 1, 1, 1.0f);
    mat2_write_float(trans_mat, 2, 2, 1.0f);
    mat2_write_float(trans_mat, 3, 3, 1.0f);
    mat2_write_float(trans_mat, 3, 0, v->x);
    mat2_write_float(trans_mat, 3, 1, v->y);
    mat2_write_float(trans_mat, 3, 2, v->z);

    return trans_mat;
}

struct Mat2 *matrix_create_x_rotation(float x_rot)
{
    float angle_radians = degrees_to_radians(x_rot);

    struct Mat2 *x_rot_mat = mat2_create(4, 4, MAT2_FLOAT);

    mat2_write_float(x_rot_mat, 0, 0, 1.0f);
    mat2_write_float(x_rot_mat, 1, 1, cosf(angle_radians));
    mat2_write_float(x_rot_mat, 1, 2, sinf(angle_radians));
    mat2_write_float(x_rot_mat, 2, 1, -sinf(angle_radians));
    mat2_write_float(x_rot_mat, 2, 2, cosf(angle_radians));
    mat2_write_float(x_rot_mat, 3, 3, 1.0f);

    return x_rot_mat;
}

struct Mat2 *matrix_create_y_rotation(float y_rot)
{
    float angle_radians = degrees_to_radians(y_rot);

    struct Mat2 *y_rot_mat = mat2_create(4, 4, MAT2_FLOAT);

    mat2_write_float(y_rot_mat, 0, 0, cosf(angle_radians));
    mat2_write_float(y_rot_mat, 0, 2, sinf(angle_radians));
    mat2_write_float(y_rot_mat, 1, 1, 1.0f);
    mat2_write_float(y_rot_mat, 2, 0, -sinf(angle_radians));
    mat2_write_float(y_rot_mat, 2, 2, cosf(angle_radians));
    mat2_write_float(y_rot_mat, 3, 3, 1.0f);

    return y_rot_mat;
}

struct Mat2 *matrix_create_z_rotation(float z_rot)
{
    float angle_radians = degrees_to_radians(z_rot);

    struct Mat2 *z_rot_mat = mat2_create(4, 4, MAT2_FLOAT);

    mat2_write_float(z_rot_mat, 0, 0, cosf(angle_radians));
    mat2_write_float(z_rot_mat, 0, 1, sinf(angle_radians));
    mat2_write_float(z_rot_mat, 1, 0, -sinf(angle_radians));
    mat2_write_float(z_rot_mat, 1, 1, cosf(angle_radians));
    mat2_write_float(z_rot_mat, 2, 2, 1.0f);
    mat2_write_float(z_rot_mat, 3, 3, 1.0f);

    return z_rot_mat;
}
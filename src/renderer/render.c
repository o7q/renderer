#include "render.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "math/matrix.h"
#include "math/angle.h"

static struct Mat2 *render_create_projection_matrix(struct Camera *camera, struct Viewport *viewport)
{
    float fovRad = 1.0f / tanf(degrees_to_radians(camera->fov / 2.0f));

    struct Mat2 *projection_matrix = mat2_create(4, 4, MAT2_FLOAT);

    mat2_write_float(projection_matrix, 0, 0, viewport->aspect * fovRad);
    mat2_write_float(projection_matrix, 1, 1, fovRad);
    mat2_write_float(projection_matrix, 2, 2, camera->clip_far / (camera->clip_far - camera->clip_near));
    mat2_write_float(projection_matrix, 3, 2, (-camera->clip_far * camera->clip_near) / (camera->clip_far - camera->clip_near));
    mat2_write_float(projection_matrix, 2, 3, 1.0f);
    mat2_write_float(projection_matrix, 3, 3, 0.0f);

    return projection_matrix;
}

static struct Mat2 *render_create_x_rotation_matrix(struct Camera *camera)
{
    float angle_radians = degrees_to_radians(camera->rotation.x);

    struct Mat2 *x_rot_matrix = mat2_create(4, 4, MAT2_FLOAT);

    mat2_write_float(x_rot_matrix, 0, 0, 1.0f);
    mat2_write_float(x_rot_matrix, 1, 1, cosf(angle_radians));
    mat2_write_float(x_rot_matrix, 1, 2, sinf(angle_radians));
    mat2_write_float(x_rot_matrix, 2, 1, -sinf(angle_radians));
    mat2_write_float(x_rot_matrix, 2, 2, cosf(angle_radians));
    mat2_write_float(x_rot_matrix, 3, 3, 1.0f);

    return x_rot_matrix;
}

static struct Mat2 *render_create_y_rotation_matrix(struct Camera *camera)
{
    float angle_radians = degrees_to_radians(camera->rotation.y);

    struct Mat2 *y_rot_matrix = mat2_create(4, 4, MAT2_FLOAT);

    mat2_write_float(y_rot_matrix, 0, 0, cosf(angle_radians));
    mat2_write_float(y_rot_matrix, 0, 2, sinf(angle_radians));
    mat2_write_float(y_rot_matrix, 1, 1, 1.0f);
    mat2_write_float(y_rot_matrix, 2, 0, -sinf(angle_radians));
    mat2_write_float(y_rot_matrix, 2, 2, cosf(angle_radians));
    mat2_write_float(y_rot_matrix, 3, 3, 1.0f);

    return y_rot_matrix;
}

static struct Mat2 *render_create_z_rotation_matrix(struct Camera *camera)
{
    float angle_radians = degrees_to_radians(camera->rotation.z);

    struct Mat2 *z_rot_matrix = mat2_create(4, 4, MAT2_FLOAT);

    mat2_write_float(z_rot_matrix, 0, 0, cosf(angle_radians));
    mat2_write_float(z_rot_matrix, 0, 1, sinf(angle_radians));
    mat2_write_float(z_rot_matrix, 1, 0, -sinf(angle_radians));
    mat2_write_float(z_rot_matrix, 1, 1, cosf(angle_radians));
    mat2_write_float(z_rot_matrix, 2, 2, 1.0f);
    mat2_write_float(z_rot_matrix, 3, 3, 1.0f);

    return z_rot_matrix;
}

static void render_draw_line(struct Mat2 *render_projection, int x1, int y1, int x2, int y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float adx = abs(dx);
    float ady = abs(dy);
    float step = adx > ady ? adx : ady;

    if (step < 0.1f || step > 1000.0f)
    {
        return;
    }

    float stepX = dx / step;
    float stepY = dy / step;

    for (int j = 0; j < step + 1; ++j)
    {
        int x = round(x1 + j * stepX);
        int y = round(y1 + j * stepY);

        mat2_write_float(render_projection, y, x, 0.5f);
    }
}

static struct Mat2 *render_project(struct World *world, struct Camera *camera, struct Viewport *viewport)
{
    struct Mat2 *render_projection = mat2_create(viewport->height, viewport->width, MAT2_FLOAT);

    struct Mat2 *projection_matrix = render_create_projection_matrix(camera, viewport);

    struct Mat2 *x_rot_matrix = render_create_x_rotation_matrix(camera);
    struct Mat2 *y_rot_matrix = render_create_y_rotation_matrix(camera);
    struct Mat2 *z_rot_matrix = render_create_z_rotation_matrix(camera);

    for (int i = 0; i < world->tri_index; ++i)
    {
        struct Triangle tri = world->tris[i];
        struct Triangle tri_rotated_x = tri;
        struct Triangle tri_rotated_xy = tri;
        struct Triangle tri_rotated_xyz = tri;

        struct Triangle tri_rotated_projected = tri;

        vec3_multiply_mat2_4x4(x_rot_matrix, tri.a, &tri_rotated_x.a);
        vec3_multiply_mat2_4x4(x_rot_matrix, tri.b, &tri_rotated_x.b);
        vec3_multiply_mat2_4x4(x_rot_matrix, tri.c, &tri_rotated_x.c);

        vec3_multiply_mat2_4x4(y_rot_matrix, tri_rotated_x.a, &tri_rotated_xy.a);
        vec3_multiply_mat2_4x4(y_rot_matrix, tri_rotated_x.b, &tri_rotated_xy.b);
        vec3_multiply_mat2_4x4(y_rot_matrix, tri_rotated_x.c, &tri_rotated_xy.c);

        vec3_multiply_mat2_4x4(z_rot_matrix, tri_rotated_xy.a, &tri_rotated_xyz.a);
        vec3_multiply_mat2_4x4(z_rot_matrix, tri_rotated_xy.b, &tri_rotated_xyz.b);
        vec3_multiply_mat2_4x4(z_rot_matrix, tri_rotated_xy.c, &tri_rotated_xyz.c);

        vec3_multiply_mat2_4x4(projection_matrix, (struct Vec3){tri_rotated_xyz.a.x + camera->position.x, tri_rotated_xyz.a.y + camera->position.y, tri_rotated_xyz.a.z + camera->position.z}, &tri_rotated_projected.a);
        vec3_multiply_mat2_4x4(projection_matrix, (struct Vec3){tri_rotated_xyz.b.x + camera->position.x, tri_rotated_xyz.b.y + camera->position.y, tri_rotated_xyz.b.z + camera->position.z}, &tri_rotated_projected.b);
        vec3_multiply_mat2_4x4(projection_matrix, (struct Vec3){tri_rotated_xyz.c.x + camera->position.x, tri_rotated_xyz.c.y + camera->position.y, tri_rotated_xyz.c.z + camera->position.z}, &tri_rotated_projected.c);

        tri_rotated_projected.a.x += 1.0f;
        tri_rotated_projected.a.y += 1.0f;
        tri_rotated_projected.b.x += 1.0f;
        tri_rotated_projected.b.y += 1.0f;
        tri_rotated_projected.c.x += 1.0f;
        tri_rotated_projected.c.y += 1.0f;

        tri_rotated_projected.a.x *= 0.5f * (float)viewport->width;
        tri_rotated_projected.a.y *= 0.5f * (float)viewport->height;
        tri_rotated_projected.b.x *= 0.5f * (float)viewport->width;
        tri_rotated_projected.b.y *= 0.5f * (float)viewport->height;
        tri_rotated_projected.c.x *= 0.5f * (float)viewport->width;
        tri_rotated_projected.c.y *= 0.5f * (float)viewport->height;

        render_draw_line(render_projection, (int)tri_rotated_projected.a.x, (int)tri_rotated_projected.a.y, (int)tri_rotated_projected.b.x, (int)tri_rotated_projected.b.y);
        render_draw_line(render_projection, (int)tri_rotated_projected.b.x, (int)tri_rotated_projected.b.y, (int)tri_rotated_projected.c.x, (int)tri_rotated_projected.c.y);
        render_draw_line(render_projection, (int)tri_rotated_projected.c.x, (int)tri_rotated_projected.c.y, (int)tri_rotated_projected.a.x, (int)tri_rotated_projected.a.y);

        mat2_write_float(render_projection, (int)tri_rotated_projected.a.y, (int)tri_rotated_projected.a.x, 1.0f);
        mat2_write_float(render_projection, (int)tri_rotated_projected.b.y, (int)tri_rotated_projected.b.x, 1.0f);
        mat2_write_float(render_projection, (int)tri_rotated_projected.c.y, (int)tri_rotated_projected.c.x, 1.0f);
    }

    mat2_delete(projection_matrix);

    return render_projection;
}

static struct Mat2 *render_rasterize(struct Mat2 *render_projection)
{
    struct Mat2 *render_rasterized = mat2_create(render_projection->height, render_projection->width * 2 + 1, MAT2_CHAR);

    for (int y = 0; y < render_projection->height; ++y)
    {
        int raster_x_index = 0;
        for (int x = 0; x < render_projection->width; ++x)
        {
            char pixel = '\0';
            float value = mat2_read_float(render_projection, y, x);
            if (value > 0.5f)
            {
                pixel = '@';
            }
            else if (value > 0.0f)
            {
                pixel = '.';
            }
            mat2_write_char(render_rasterized, y, raster_x_index, pixel);
            mat2_write_char(render_rasterized, y, raster_x_index + 1, pixel);
            raster_x_index += 2;
        }

        mat2_write_char(render_rasterized, y, raster_x_index, '\n');
    }

    return render_rasterized;
}

void render(struct World *world, struct Camera *camera, struct Viewport *viewport)
{
    struct Mat2 *render_projection = render_project(world, camera, viewport);
    struct Mat2 *render_rasterized = render_rasterize(render_projection);

    fwrite(render_rasterized->data, 1, render_rasterized->area, stdout);

    mat2_delete(render_projection);
    mat2_delete(render_rasterized);
}
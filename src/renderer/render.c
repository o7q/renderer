#include "render.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "math/matrix.h"
#include "math/angle.h"
#include "math/vector.h"
#include "math/matrix_math.h"

static void render_draw_line(struct Mat2 *render_projection, int x1, int y1, int x2, int y2)
{
    // a simple line drawing algorithm
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

    struct Mat2 *projection_matrix = matrix_create_projection(camera->fov, viewport->aspect, camera->clip_near, camera->clip_far);

    struct Mat2 *x_rot_matrix = matrix_create_x_rotation(camera->rotation.x);
    struct Mat2 *y_rot_matrix = matrix_create_y_rotation(camera->rotation.y);
    struct Mat2 *z_rot_matrix = matrix_create_z_rotation(camera->rotation.z);

    for (int i = 0; i < world->tri_index; ++i)
    {
        // setup vectors for rotations
        struct Triangle tri = world->tris[i];

        // we will be stacking rotations upon eachother, starting first with the x-axis

        // rotate on the x-axis
        struct Triangle tri_rotated_x = (struct Triangle){matrix_multiply_vector_4x4(x_rot_matrix, &tri.a),
                                                          matrix_multiply_vector_4x4(x_rot_matrix, &tri.b),
                                                          matrix_multiply_vector_4x4(x_rot_matrix, &tri.c)};

        // rotate on the y-axis
        struct Triangle tri_rotated_xy = (struct Triangle){matrix_multiply_vector_4x4(y_rot_matrix, &tri_rotated_x.a),
                                                           matrix_multiply_vector_4x4(y_rot_matrix, &tri_rotated_x.b),
                                                           matrix_multiply_vector_4x4(y_rot_matrix, &tri_rotated_x.c)};

        // finally, rotate on the z-axis
        struct Triangle tri_rotated_xyz = (struct Triangle){matrix_multiply_vector_4x4(z_rot_matrix, &tri_rotated_xy.a),
                                                            matrix_multiply_vector_4x4(z_rot_matrix, &tri_rotated_xy.b),
                                                            matrix_multiply_vector_4x4(z_rot_matrix, &tri_rotated_xy.c)};

        // translate the point
        struct Triangle tri_rotated_translated = tri_rotated_xyz;
        tri_rotated_translated.a = (struct Vec3){tri_rotated_xyz.a.x + 10, tri_rotated_xyz.a.y + 20, tri_rotated_xyz.a.z + 30};
        tri_rotated_translated.b = (struct Vec3){tri_rotated_xyz.b.x + 10, tri_rotated_xyz.b.y + 20, tri_rotated_xyz.b.z + 30};
        tri_rotated_translated.c = (struct Vec3){tri_rotated_xyz.c.x + 10, tri_rotated_xyz.c.y + 20, tri_rotated_xyz.c.z + 30};

        struct Vec3 line1 = vec3_subtract(&tri_rotated_translated.b, &tri_rotated_translated.a);
        struct Vec3 line2 = vec3_subtract(&tri_rotated_translated.c, &tri_rotated_translated.a);

        // the normal of the triangle, which is not yet normalized
        struct Vec3 normal = vec3_cross(&line1, &line2);

        // let's normalize the normal!
        struct Vec3 normal_normalized = vec3_normalize(&normal);

        // if (1)
        if (normal_normalized.x * (tri_rotated_translated.a.x - camera->position.x) +
                normal_normalized.y * (tri_rotated_translated.a.y - camera->position.y) +
                normal_normalized.z * (tri_rotated_translated.a.z - camera->position.z) <
            0.0f)
        {
            struct Triangle tri_rotated_projected = (struct Triangle){matrix_multiply_vector_4x4(projection_matrix, &tri_rotated_translated.a),
                                                                      matrix_multiply_vector_4x4(projection_matrix, &tri_rotated_translated.b),
                                                                      matrix_multiply_vector_4x4(projection_matrix, &tri_rotated_translated.c)};

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
    }

    // clean up matricies
    mat2_delete(projection_matrix);
    mat2_delete(x_rot_matrix);
    mat2_delete(y_rot_matrix);
    mat2_delete(z_rot_matrix);

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
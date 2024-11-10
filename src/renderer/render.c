#include "render.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "math/matrix.h"
#include "math/angle.h"

static struct Mat2 *render_project(struct World *world, struct Camera *camera, struct Viewport *viewport)
{
    struct Mat2 *render_projection = mat2_create(viewport->height, viewport->width, MAT2_FLOAT);

    struct Mat2 *projection_matrix = mat2_create(4, 4, MAT2_FLOAT);

    float fovRad = 1.0f / tanf(degrees_to_radians(camera->fov / 2.0f));

    mat2_write_float(projection_matrix, 0, 0, viewport->aspect * fovRad);
    mat2_write_float(projection_matrix, 1, 1, fovRad);
    mat2_write_float(projection_matrix, 2, 2, camera->clip_far / (camera->clip_far - camera->clip_near));
    mat2_write_float(projection_matrix, 3, 2, (-camera->clip_far * camera->clip_near) / (camera->clip_far - camera->clip_near));
    mat2_write_float(projection_matrix, 2, 3, 1.0f);
    mat2_write_float(projection_matrix, 3, 3, 0.0f);

    for (int i = 0; i < world->tri_index; ++i)
    {
        struct Triangle tri = world->tris[i];

        struct Vec3 a = vec3_multiply_mat2_4x4(projection_matrix, (struct Vec3){tri.a.x + camera->position.x, tri.a.y + camera->position.y, tri.a.z + camera->position.z});
        struct Vec3 b = vec3_multiply_mat2_4x4(projection_matrix, (struct Vec3){tri.b.x + camera->position.x, tri.b.y + camera->position.y, tri.b.z + camera->position.z});
        struct Vec3 c = vec3_multiply_mat2_4x4(projection_matrix, (struct Vec3){tri.c.x + camera->position.x, tri.c.y + camera->position.y, tri.c.z + camera->position.z});

        a.x += 1.0f; a.y += 1.0f;
        b.x += 1.0f; b.y += 1.0f;
        c.x += 1.0f; c.y += 1.0f;

        a.x *= 0.5f * (float)viewport->width;
        a.y *= 0.5f * (float)viewport->height;
        b.x *= 0.5f * (float)viewport->width;
        b.y *= 0.5f * (float)viewport->height;
        c.x *= 0.5f * (float)viewport->width;
        c.y *= 0.5f * (float)viewport->height;

        mat2_write_float(render_projection, (int)a.y, (int)a.x, 1.0f);
        mat2_write_float(render_projection, (int)b.y, (int)b.x, 1.0f);
        mat2_write_float(render_projection, (int)c.y, (int)c.x, 1.0f);

        // float dx = b.x - a.x;
        // float dy = b.y - a.y;

        // float adx = abs(dx);
        // float ady = abs(dy);
        // float step = adx > ady ? adx : ady;

        // if (step < 0.1f || step > 10.0f)
        // {
        //     continue;
        // }

        // float stepX = dx / step;
        // float stepY = dy / step;

        // for (int j = 0; j < step + 1; ++j)
        // {
        //     int x = round(a.x + j * stepX);
        //     int y = round(a.y + j * stepY);

        //     mat2_write_float(render_projection, y, x, 1.0f);
        // }
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
            char pixel = mat2_read_float(render_projection, y, x) > 0.0f ? '@' : '\0';
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
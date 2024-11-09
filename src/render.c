#include "render.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "matrix.h"
#include "trig.h"

void render_world(struct World *world, struct Camera *camera)
{
    char characters[] = "@#*,.";
    int characters_length = 5;

    int pixel_count = camera->width * camera->height;

    char *screen_stream = (char *)malloc(pixel_count * sizeof(char));
    memset(screen_stream, ' ', pixel_count * sizeof(char));

    for (int i = 0; i < world->segment_index; ++i)
    {
        struct Point rotated_point1 = rotate_point(&world->segments[i].a, camera);
        struct Point rotated_point2 = rotate_point(&world->segments[i].b, camera);

        struct Point projected_point1 = project_point(&rotated_point1, camera);
        struct Point projected_point2 = project_point(&rotated_point2, camera);

        // float dx = projected_point2.x - projected_point1.x;
        // float dy = projected_point2.y - projected_point1.y;

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
        //     int x = round(projected_point1.x + j * stepX);
        //     int y = round(projected_point1.y + j * stepY);

        //     int pixel_index = matrix_get_1d_index(y, x, camera->width);

        //     if (x < camera->width && x >= 0 && y < camera->height && y >= 0)
        //     {
        //         screen_stream[pixel_index] = '.';
        //     }
        // }

        if (matrix_in_range(projected_point1.y, projected_point1.x, camera->height, camera->width))
        {
            float distance = distance_3d(&world->segments[i].a, &camera->position);
            int pixel_index = matrix_get_1d_index(projected_point1.y, projected_point1.x, camera->width);
            // if (distance > characters_length - 1)
            // {
            //     distance = characters_length - 1;
            // }
            screen_stream[pixel_index] = '.';
        }
        if (matrix_in_range(projected_point2.y, projected_point2.x, camera->height, camera->width))
        {
            float distance = distance_3d(&world->segments[i].b, &camera->position);
            int pixel_index = matrix_get_1d_index(projected_point2.y, projected_point2.x, camera->width);

            // if (distance > characters_length - 1)
            // {
            //     distance = characters_length - 1;
            // }
            screen_stream[pixel_index] = '.';
        }
    }

    char *screen = (char *)malloc((pixel_count * 2 + camera->height) * sizeof(char));

    int total_index = 0;
    for (int y = 0; y < camera->height; ++y)
    {
        for (int x = 0; x < camera->width; ++x)
        {
            int index = matrix_get_1d_index(y, x, camera->width);
            screen[total_index] = screen_stream[index];
            screen[total_index + 1] = screen_stream[index];
            total_index += 2;
        }
        screen[total_index] = '\n';
        total_index += 1;
    }

    fwrite(screen, 1, pixel_count * 2 + camera->height, stdout);
    putchar('\n');

    free(screen_stream);
    free(screen);
}
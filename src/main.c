#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "geo/geo.h"
#include "world.h"
#include "render.h"
#include "console.h"

int main(void)
{
    struct World *world = world_create(100000);
    struct Camera *camera = camera_create(100, 50);

    for (int x = 0; x < 5; ++x)
    {
        for (int y = 0; y < 5; ++y)
        {
            for (int z = 0; z < 5; ++z)
            {
                struct Segment *cube = geo_create_cube((struct Point){20 * x, 20 * y, 20 * z}, 10);
                world_add_object(world, cube, 12);
            }
        }
    }

    // struct Segment test = (struct Segment){(struct Point){0, 0, 0}, (struct Point){10, 10, 10}};

    // world_add_object(world, &test, 1);

    bool running = true;

    while (running)
    {
        // w
        if (key_pressed(0x57))
        {
            camera->position.z -= 0.1f;
        }
        // s
        if (key_pressed(0x53))
        {
            camera->position.z += 0.1f;
        }
        // a
        if (key_pressed(0x41))
        {
            camera->position.x += 0.1f;
        }
        // d
        if (key_pressed(0x44))
        {
            camera->position.x -= 0.1f;
        }
        // space
        if (key_pressed(0x20))
        {
            camera->position.y += 0.1f;
        }
        // shift
        if (key_pressed(0xA0))
        {
            camera->position.y -= 0.1f;
        }
        // up
        if (key_pressed(0x26))
        {
            camera->rotation.x += 0.1f;
        }
        // down
        if (key_pressed(0x28))
        {
            camera->rotation.x -= 0.1f;
        }
        // left
        if (key_pressed(0x25))
        {
            camera->rotation.y -= 0.1f;
        }
        // right
        if (key_pressed(0x27))
        {
            camera->rotation.y += 0.1f;
        }

        render_world(world, camera);

        char buffer[256];

        int len = snprintf(buffer, sizeof(buffer),
                           "X: %.3f Y: %.3f Z: %.3f\nRX: %.3f RY: %.3f RZ: %.3f",
                           camera->position.x,
                           camera->position.y,
                           camera->position.z,
                           camera->rotation.x,
                           camera->rotation.y,
                           camera->rotation.z);

        fwrite(buffer, sizeof(char), len, stdout);

        clear_screen();
    }

    world_delete(world);

    getchar();
    return 0;
}
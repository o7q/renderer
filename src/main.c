#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "renderer.h"
#include "input.h"

int main(void)
{
    struct World *world = world_create(100000);
    struct Camera *camera = camera_create();
    struct Viewport *viewport = viewport_create(100, 50);

    struct Mesh *cube = geometry_create_cube();

    world_add_mesh(world, cube);

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
        // z
        if (key_pressed(0x5A))
        {
            camera->fov -= 0.1f;
        }
        // x
        if (key_pressed(0x58))
        {
            camera->fov += 0.1f;
        }

        render(world, camera, viewport);

        char buffer[256];

        int len = snprintf(buffer, sizeof(buffer),
                           "X: %.3f Y: %.3f Z: %.3f\nRX: %.3f RY: %.3f RZ: %.3f\nFOV: %.3f",
                           camera->position.x,
                           camera->position.y,
                           camera->position.z,
                           camera->rotation.x,
                           camera->rotation.y,
                           camera->rotation.z,
                           camera->fov);

        fwrite(buffer, sizeof(char), len, stdout);

        clear_screen();
    }

    world_delete(world);

    getchar();
    return 0;
}
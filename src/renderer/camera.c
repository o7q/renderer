#include "camera.h"

#include <stdlib.h>

struct Camera *camera_create()
{
    struct Camera *camera = malloc(sizeof(struct Camera));

    if (!camera)
    {
        return NULL;
    }

    camera->position = (struct Vec3){0.0f, 0.0f, 0.0f};
    camera->rotation = (struct Vec3){0.0f, 0.0f, 0.0f};

    camera->fov = 90.0f;

    camera->clip_near = 1.0f;
    camera->clip_far = 1000.0f;

    return camera;
}
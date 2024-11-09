#include "camera.h"

#include <stdlib.h>

struct Camera *camera_create(int width, int height)
{
    struct Camera *camera = (struct Camera *)malloc(sizeof(struct Camera));

    camera->width = width;
    camera->height = height;

    camera->position = (struct Point){0, 0, 0};
    camera->rotation = (struct Point){0, 0, 0};
    camera->focal_length = 80.0f;

    return camera;
}
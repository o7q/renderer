#include "viewport.h"

#include <stdlib.h>

struct Viewport *viewport_create(int width, int height)
{
    struct Viewport *viewport = malloc(sizeof(struct Viewport));

    if (!viewport)
    {
        return NULL;
    }

    viewport->width = width;
    viewport->height = height;

    viewport->area = width * height;

    viewport->aspect = height / (float)width;

    return viewport;
}
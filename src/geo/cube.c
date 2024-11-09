#include "geo.h"

#include <stdlib.h>

struct Segment *geo_create_cube(struct Point location, float size)
{
    struct Segment *cube = (struct Segment *)malloc(12 * sizeof(struct Segment));

    cube[0].a.x = 0;
    cube[0].a.y = 0;
    cube[0].a.z = 0;
    cube[0].b.x = 0;
    cube[0].b.y = 0;
    cube[0].b.z = 1.0f;

    cube[1].a.x = 0;
    cube[1].a.y = 0;
    cube[1].a.z = 1.0f;
    cube[1].b.x = 1.0f;
    cube[1].b.y = 0;
    cube[1].b.z = 1.0f;

    cube[2].a.x = 1.0f;
    cube[2].a.y = 0;
    cube[2].a.z = 1.0f;
    cube[2].b.x = 1.0f;
    cube[2].b.y = 0;
    cube[2].b.z = 0;

    cube[3].a.x = 1.0f;
    cube[3].a.y = 0;
    cube[3].a.z = 0;
    cube[3].b.x = 0;
    cube[3].b.y = 0;
    cube[3].b.z = 0;

    cube[4].a.x = 0;
    cube[4].a.y = 0;
    cube[4].a.z = 0;
    cube[4].b.x = 0;
    cube[4].b.y = 1.0f;
    cube[4].b.z = 0;

    cube[5].a.x = 0;
    cube[5].a.y = 0;
    cube[5].a.z = 1.0f;
    cube[5].b.x = 0;
    cube[5].b.y = 1.0f;
    cube[5].b.z = 1.0f;

    cube[6].a.x = 1.0f;
    cube[6].a.y = 0;
    cube[6].a.z = 1.0f;
    cube[6].b.x = 1.0f;
    cube[6].b.y = 1.0f;
    cube[6].b.z = 1.0f;

    cube[7].a.x = 1.0f;
    cube[7].a.y = 0;
    cube[7].a.z = 0;
    cube[7].b.x = 1.0f;
    cube[7].b.y = 1.0f;
    cube[7].b.z = 0;

    cube[8].a.x = 0;
    cube[8].a.y = 1.0f;
    cube[8].a.z = 0;
    cube[8].b.x = 0;
    cube[8].b.y = 1.0f;
    cube[8].b.z = 1.0f;

    cube[9].a.x = 0;
    cube[9].a.y = 1.0f;
    cube[9].a.z = 1.0f;
    cube[9].b.x = 1.0f;
    cube[9].b.y = 1.0f;
    cube[9].b.z = 1.0f;

    cube[10].a.x = 1.0f;
    cube[10].a.y = 1.0f;
    cube[10].a.z = 1.0f;
    cube[10].b.x = 1.0f;
    cube[10].b.y = 1.0f;
    cube[10].b.z = 0;

    cube[11].a.x = 1.0f;
    cube[11].a.y = 1.0f;
    cube[11].a.z = 0;
    cube[11].b.x = 0;
    cube[11].b.y = 1.0f;
    cube[11].b.z = 0;

    for (int i = 0; i < 12; ++i)
    {
        cube[i].a.x = cube[i].a.x * size + location.x;
        cube[i].a.y = cube[i].a.y * size + location.y;
        cube[i].a.z = cube[i].a.z * size + location.z;

        cube[i].b.x = cube[i].b.x * size + location.x;
        cube[i].b.y = cube[i].b.y * size + location.y;
        cube[i].b.z = cube[i].b.z * size + location.z;
    }

    return cube;
}
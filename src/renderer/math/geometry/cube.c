#include "geometry.h"

#include <stdlib.h>

struct Mesh *geometry_create_cube()
{
    struct Mesh *cube = malloc(sizeof(struct Mesh));

    cube->tri_count = 12;
    cube->tris = malloc(cube->tri_count * sizeof(struct Triangle));

    // south
    cube->tris[0].a = (struct Vec3){0.0f, 0.0f, 0.0f};
    cube->tris[0].b = (struct Vec3){0.0f, 1.0f, 0.0f};
    cube->tris[0].c = (struct Vec3){1.0f, 1.0f, 0.0f};

    cube->tris[1].a = (struct Vec3){0.0f, 0.0f, 0.0f};
    cube->tris[1].b = (struct Vec3){1.0f, 1.0f, 0.0f};
    cube->tris[1].c = (struct Vec3){1.0f, 0.0f, 0.0f};

    // east
    cube->tris[2].a = (struct Vec3){1.0f, 0.0f, 0.0f};
    cube->tris[2].b = (struct Vec3){1.0f, 1.0f, 0.0f};
    cube->tris[2].c = (struct Vec3){1.0f, 1.0f, 1.0f};

    cube->tris[3].a = (struct Vec3){1.0f, 0.0f, 0.0f};
    cube->tris[3].b = (struct Vec3){1.0f, 1.0f, 1.0f};
    cube->tris[3].c = (struct Vec3){1.0f, 0.0f, 1.0f};

    // north
    cube->tris[4].a = (struct Vec3){1.0f, 0.0f, 1.0f};
    cube->tris[4].b = (struct Vec3){1.0f, 1.0f, 1.0f};
    cube->tris[4].c = (struct Vec3){0.0f, 1.0f, 1.0f};

    cube->tris[5].a = (struct Vec3){1.0f, 0.0f, 1.0f};
    cube->tris[5].b = (struct Vec3){0.0f, 1.0f, 1.0f};
    cube->tris[5].c = (struct Vec3){0.0f, 0.0f, 1.0f};

    // west
    cube->tris[6].a = (struct Vec3){0.0f, 0.0f, 1.0f};
    cube->tris[6].b = (struct Vec3){0.0f, 1.0f, 1.0f};
    cube->tris[6].c = (struct Vec3){0.0f, 1.0f, 0.0f};

    cube->tris[7].a = (struct Vec3){0.0f, 0.0f, 1.0f};
    cube->tris[7].b = (struct Vec3){0.0f, 1.0f, 0.0f};
    cube->tris[7].c = (struct Vec3){0.0f, 0.0f, 0.0f};

    // top
    cube->tris[8].a = (struct Vec3){0.0f, 1.0f, 0.0f};
    cube->tris[8].b = (struct Vec3){0.0f, 1.0f, 1.0f};
    cube->tris[8].c = (struct Vec3){1.0f, 1.0f, 1.0f};

    cube->tris[9].a = (struct Vec3){0.0f, 1.0f, 0.0f};
    cube->tris[9].b = (struct Vec3){1.0f, 1.0f, 1.0f};
    cube->tris[9].c = (struct Vec3){1.0f, 1.0f, 0.0f};

    // bottom
    cube->tris[10].a = (struct Vec3){1.0f, 0.0f, 1.0f};
    cube->tris[10].b = (struct Vec3){0.0f, 0.0f, 1.0f};
    cube->tris[10].c = (struct Vec3){0.0f, 0.0f, 0.0f};

    cube->tris[11].a = (struct Vec3){1.0f, 0.0f, 1.0f};
    cube->tris[11].b = (struct Vec3){0.0f, 0.0f, 0.0f};
    cube->tris[11].c = (struct Vec3){1.0f, 0.0f, 0.0f};

    for (int i = 0; i < cube->tri_count; ++i)
    {
        cube->tris[i].a.x *= 10.0f;
        cube->tris[i].a.y *= 10.0f;
        cube->tris[i].a.z *= 10.0f;
        
        cube->tris[i].b.x *= 10.0f;
        cube->tris[i].b.y *= 10.0f;
        cube->tris[i].b.z *= 10.0f;

        cube->tris[i].c.x *= 10.0f;
        cube->tris[i].c.y *= 10.0f;
        cube->tris[i].c.z *= 10.0f;
    }

    return cube;
}
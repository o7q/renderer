#include "world.h"

#include <stdio.h>
#include <stdlib.h>

struct World *world_create(int max_tris)
{
    struct World *world = malloc(sizeof(struct World));

    if (!world)
    {
        return NULL;
    }

    world->tris = calloc(max_tris, sizeof(struct Triangle));
    world->max_tris = max_tris;
    world->tri_index = 0;

    if (!world->tris)
    {
        free(world);
        return NULL;
    }

    return world;
}

void world_delete(struct World *world)
{
    if (world)
    {
        if (world->tris)
        {
            free(world->tris);
        }
        free(world);
    }
}

void world_add_mesh(struct World *world, struct Mesh *mesh)
{
    if (!world ||
        !mesh ||
        world->tri_index + mesh->tri_count > world->max_tris ||
        mesh->tri_count <= 0)
    {
        return;
    }

    for (int i = 0; i < mesh->tri_count; ++i)
    {
        world->tris[world->tri_index] = mesh->tris[i];
        ++world->tri_index;
    }
}
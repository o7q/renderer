#ifndef WORLD_H
#define WORLD_H

#include "math/geometry/geometry.h"

struct World
{
    struct Triangle *tris;
    int max_tris;
    int tri_index;
};

struct World *world_create(int max_tris);
void world_delete(struct World *world);

void world_add_mesh(struct World *world, struct Mesh *mesh);

#endif
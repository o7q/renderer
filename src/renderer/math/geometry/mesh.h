#ifndef MESH_H
#define MESH_H

#include "types.h"

struct Mesh *mesh_init(int tri_count);
void mesh_delete(struct Mesh *mesh);

struct Mesh *mesh_create_cube(float x, float y, float z);

#endif
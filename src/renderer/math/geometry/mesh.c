#include "mesh.h"

#include <stdlib.h>

struct Mesh *mesh_init(int tri_count)
{
    struct Mesh *mesh = malloc(sizeof(struct Mesh));

    mesh->tri_count = tri_count;
    mesh->tris = malloc(tri_count * sizeof(struct Triangle));

    return mesh;
}

void mesh_delete(struct Mesh *mesh)
{
    if (mesh)
    {
        if (mesh->tris)
        {
            free(mesh->tris);
        }
        free(mesh);
    }
}
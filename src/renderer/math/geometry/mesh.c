#include "geometry.h"

#include <stdlib.h>

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
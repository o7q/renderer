#ifndef GEOMETRY_H
#define GEOMETRY_H

struct Vec3
{
    float x;
    float y;
    float z;
};

struct Triangle
{
    struct Vec3 a;
    struct Vec3 b;
    struct Vec3 c;
};

struct Mesh
{
    int tri_count;
    struct Triangle *tris;
};

struct Mesh *geometry_create_cube();

void mesh_delete(struct Mesh *mesh);

#endif
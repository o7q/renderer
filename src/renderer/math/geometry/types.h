#ifndef TYPES_H
#define TYPES_H

struct Vec3
{
    float x;
    float y;
    float z;

    // extra value, helpful for some matrix operations
    float w;
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

#endif
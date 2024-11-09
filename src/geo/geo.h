#ifndef GEO_H
#define GEO_H

struct Point
{
    float x;
    float y;
    float z;
};

struct Segment
{
    struct Point a;
    struct Point b;
};

struct Segment *geo_create_cube(struct Point location, float size);

#endif
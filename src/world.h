#ifndef WORLD_H
#define WORLD_H

#include "geo/geo.h"

struct World
{
    struct Segment *segments;
    int segment_index;
};

struct World *world_create(int max_segments);
void world_delete(struct World *world);

void world_add_object(struct World *world, struct Segment *shape, int segment_count);

#endif
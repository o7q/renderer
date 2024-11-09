#include "world.h"

#include <stdio.h>
#include <stdlib.h>

struct World *world_create(int max_segments)
{
    struct World *world = (struct World *)malloc(sizeof(struct World));

    world->segments = (struct Segment *)malloc(max_segments * sizeof(struct Segment));
    world->segment_index = 0;

    return world;
}

void world_delete(struct World *world)
{
    free(world->segments);
    free(world);
}

void world_add_object(struct World *world, struct Segment *object, int segment_count)
{
    for (int i = 0; i < segment_count; ++i)
    {
        world->segments[world->segment_index] = object[i];
        ++world->segment_index;
    }
}
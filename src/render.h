#ifndef RENDER_H
#define RENDER_H

#include "world.h"
#include "camera.h"

void render_world(struct World *world, struct Camera *camera);
int get_pixel_index(int x, int y, int width);
float degrees_to_radians(float degrees);

#endif
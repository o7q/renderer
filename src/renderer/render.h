#ifndef RENDER_H
#define RENDER_H

#include "world.h"
#include "camera.h"
#include "viewport.h"

void render(struct World *world, struct Camera *camera, struct Viewport *viewport);

#endif
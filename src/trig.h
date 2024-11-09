#ifndef TRIG_H
#define TRIG_H

#include "geo/geo.h"
#include "camera.h"

struct Point project_point(struct Point *point, struct Camera *camera);
struct Point rotate_point(struct Point *point, struct Camera *camera);
float degrees_to_radians(float degrees);
float distance_3d(struct Point *point1, struct Point *point2);

#endif
#ifndef CAMERA_H
#define CAMERA_H

#include "geo/geo.h"

struct Camera
{
    int width;
    int height;

    struct Point position;
    struct Point rotation;
    float focal_length;
};

struct Camera *camera_create();

#endif
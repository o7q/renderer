#ifndef CAMERA_H
#define CAMERA_H

#include "math/geometry/geometry.h"

struct Camera
{
    struct Vec3 position;
    struct Vec3 rotation;

    float fov;

    float clip_near;
    float clip_far;
};

struct Camera *camera_create();

#endif
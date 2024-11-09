#include "trig.h"

#include <math.h>

#include "camera.h"

#define PI 3.14159

struct Point project_point(struct Point *point, struct Camera *camera)
{
    struct Point screenPoint;

    float d = point->z + camera->position.z + camera->focal_length;
    screenPoint.x = ((point->x + camera->position.x) * camera->focal_length) / d + camera->width / 2.0f;
    screenPoint.y = ((point->y + camera->position.y) * camera->focal_length) / d + camera->height / 2.0f;

    return screenPoint;
}

struct Point rotate_point(struct Point *point, struct Camera *camera)
{
    float radians_x = degrees_to_radians(camera->rotation.x);
    float radians_y = degrees_to_radians(camera->rotation.y);
    float radians_z = degrees_to_radians(camera->rotation.z);

    float x = point->x + camera->position.x;
    float y = point->y + camera->position.y;
    float z = point->z + camera->position.z;

    // x rotation
    float temp_rotation_y_1 = y * cos(radians_x) + z * sin(radians_x);
    float temp_rotation_z_1 = -y * sin(radians_x) + z * cos(radians_x);

    // y rotation
    float temp_rotation_x_1 = x * cos(radians_y) - temp_rotation_z_1 * sin(radians_y);
    float temp_rotation_z_2 = x * sin(radians_y) + temp_rotation_z_1 * cos(radians_y);

    // z rotation
    float temp_rotation_x_2 = temp_rotation_x_1 * cos(radians_z) + temp_rotation_y_1 * sin(radians_z);
    float temp_rotation_y_2 = -temp_rotation_x_1 * sin(radians_z) + temp_rotation_y_1 * cos(radians_z);

    return (struct Point){
        temp_rotation_x_2 - camera->position.x,
        temp_rotation_y_2 - camera->position.y,
        temp_rotation_z_2 - camera->position.z,
    };
}

float degrees_to_radians(float degrees)
{
    return (PI / 180.0f) * degrees;
}

float distance_3d(struct Point *point1, struct Point *point2)
{
    return sqrtf(
        powf(point1->x - point2->x, 2) +
        powf(point1->y - point2->y, 2) +
        powf(point1->z - point2->z, 2));
}
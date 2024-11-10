#ifndef VIEWPORT_H
#define VIEWPORT_H

struct Viewport
{
    int width;
    int height;

    int area;

    float aspect;
};

struct Viewport* viewport_create(int width, int height);

#endif
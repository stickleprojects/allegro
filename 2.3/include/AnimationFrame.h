#include "Sprite.h"

#ifndef ANIMATIONFRAME_H
#define ANIMATIONFRAME_H

struct Rect
{
public:
    float left, top, width, height;

public:
    Rect(float l, float t, float w, float h)
    {
        left = l;
        top = t;
        width = w;
        height = h;
    }
    Rect()
    {
    }
};

class AnimationFrame
{
public:
    ALLEGRO_BITMAP *bitmap;
    int FrameTimeMax = 0;
    int FrameTime = 0;
    Rect Region;
    bool IncrementFrameTime();

    AnimationFrame *Next;
    AnimationFrame()
    {
    }
};


#endif
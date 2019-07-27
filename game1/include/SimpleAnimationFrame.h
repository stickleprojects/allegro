#include "AnimationFrame.h"

#ifndef SIMPLEANIMATIONFRAME_H
#define SIMPLEANIMATIONFRAME_H
class SimpleAnimationFrame : public AnimationFrame
{
    int FrameTimeMax = 2;
    int FrameTime = 0;
    virtual bool Update() override;
    bool IncrementFrameTime();
    ~SimpleAnimationFrame();
    
public:
SimpleAnimationFrame *Next = NULL;
    
    SimpleAnimationFrame(std::string id, ALLEGRO_BITMAP *images[],int numberOfImages, Rect region, int frameTimeMax);

    SimpleAnimationFrame(std::string id, ALLEGRO_BITMAP *bmp, Rect region, int frameTimeMax);

    void DeleteNext();
};

#endif

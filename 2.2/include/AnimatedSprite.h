#include "Sprite.h"
#include <list>

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

class AnimationFrame {
    public:
        ALLEGRO_BITMAP* bitmap;
        int FrameTimeMax = 0;
        int FrameTime = 0;
bool IncrementFrameTime();

        AnimationFrame* Next;
    
};

class AnimatedSprite : public Sprite {
private:
    AnimationFrame* firstFrame;
    
    AnimationFrame* currentFrame; // current frame
    
protected:
    ALLEGRO_BITMAP* GetImage() override;
    void NextFrame();
public:
    AnimatedSprite(ALLEGRO_BITMAP* images[], int numberOfFrames);
    ~AnimatedSprite();
    void Update() override ;
        
};

#endif

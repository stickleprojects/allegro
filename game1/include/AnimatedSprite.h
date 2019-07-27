#include "Sprite.h"
#include "SimpleAnimationFrame.h"

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H


class AnimatedSprite : public Sprite
{
private:
    AnimationFrame *firstFrame = NULL;
    AnimationFrame *currentFrame = NULL; // current frame
    bool framesOwnedByThis = true;

protected:
    ALLEGRO_BITMAP *GetImage() override;
    void NextFrame();
    void ClearFrames();
    ~AnimatedSprite();

public:
    AnimatedSprite(ALLEGRO_BITMAP *images[], int numberOfFrames);
    AnimatedSprite(AnimationFrame *first);
    void Update() override;
    bool Draw() override;
};

#endif

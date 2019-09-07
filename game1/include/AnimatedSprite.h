#include "Sprite.h"
#include "SimpleAnimationFrame.h"
#include "AnimationSet.h"

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <map>

class AnimatedSpriteWithSet: public Sprite {
protected: 
AnimationSet *animationSet = NULL;
public     :
AnimatedSpriteWithSet (AnimationSet* animationSet);

};

class AnimatedSprite : public Sprite
{
private:
    bool framesOwnedByThis = true;

protected:
    AnimationFrame *firstFrame = NULL;
    AnimationFrame *currentFrame = NULL; // current frame

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

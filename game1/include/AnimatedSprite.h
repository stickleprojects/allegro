#include "AnimationSet.h"
#include "SimpleAnimationFrame.h"
#include "Sprite.h"

#ifndef ANIMATEDSPRITE_H_
#define ANIMATEDSPRITE_H_

#include <map>

class AnimatedSprite : public Sprite {
   private:
    bool framesOwnedByThis = true;

   protected:
    AnimationSet *animationSet = NULL;
    AnimationFrame *firstFrame = NULL;
    AnimationFrame *currentFrame = NULL;   // current frame

    ALLEGRO_BITMAP *GetImage() override;
    void NextFrame();
    void ClearFrames();
    ~AnimatedSprite();

   public:
    AnimatedSprite(ALLEGRO_BITMAP *images[], int numberOfFrames);
    explicit AnimatedSprite(AnimationFrame *first);

    void Update() override;
    bool Draw() override;
};

#endif  // ANIMATEDSPRITE_H_

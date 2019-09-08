#include "Sprite.h"
#include "AnimationSet.h"

#ifndef ANIMATEDSPRITEWITHSET_H
#define ANIMATEDSPRITEWITHSET_H

#include <map>

class AnimatedSpriteWithSet : public Sprite
{
protected:
    AnimationSet *animationSet = NULL;

public:
    AnimatedSpriteWithSet(AnimationSet *animationSet);

void Update() override;
    bool Draw() override;
};

#endif

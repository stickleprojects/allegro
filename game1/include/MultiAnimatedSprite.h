#ifndef MULTIANIMATEDSPRITE_H
#define MULTIANIMATEDSPRITE_H
#include <AnimationSetFactory.h>
#include <AnimationSet.h>
#include "AnimatedSprite.h"
#include <spdlog.h>
#include <map>

class MultiAnimatedSprite : public AnimatedSprite
{
private:
    std::map<std::string, AnimationFrame *> frames;
    AnimationFrame *FindAnimationSetById(std::string id);
std::string currentAnimationSetId;
bool playAnimations=false;
void resetCurrentFrame();

public:
    MultiAnimatedSprite(AnimationSet* animationSet, std::string defaultAnimationId);
    void SetDirection(int x, int y) override;
    void Update() override;
    
};

#endif

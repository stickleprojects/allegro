#ifndef MULTIANIMATEDSPRITE_H_
#define MULTIANIMATEDSPRITE_H_

#include <AnimationSet.h>
#include <AnimationSetFactory.h>
#include <spdlog.h>
#include <map>
#include <string>
#include "AnimatedSprite.h"

class MultiAnimatedSprite : public AnimatedSprite {
   private:
    AnimationSet *animationSet;
    AnimationFrame *FindAnimationSetById(std::string id);
    std::string currentAnimationSetId;
    bool playAnimations = false;
    void resetCurrentFrame();

   public:
    MultiAnimatedSprite(AnimationSet *animationSet, std::string defaultAnimationId);
    void SetDirection(int x, int y) override;
    void Update() override;
};

#endif  // MULTIANIMATEDSPRITE_H_

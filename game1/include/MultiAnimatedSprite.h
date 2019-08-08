#ifndef MULTIANIMATEDSPRITE_H
#define MULTIANIMATEDSPRITE_H

#include "AnimatedSprite.h"
#include <map>

class MultiAnimatedSprite : public AnimatedSprite {
private:
    std::map<std::string, AnimationFrame*> frames ;
AnimationFrame* FindAnimationSetById(std::string id);
public:
    MultiAnimatedSprite(std::map<std::string,AnimationFrame*> frames, std::string defaultAnimationId);
    void SetDirection(int x, int y) ;

};


#endif


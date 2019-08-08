#include "MultiAnimatedSprite.h"


void MultiAnimatedSprite::SetDirection(int x, int y) {
    if(x>0) {
        currentFrame=FindAnimationSetById("right");
    } else if (x<0) {
        currentFrame=FindAnimationSetById("left");
    } else if (y>0) {
        currentFrame=FindAnimationSetById("down");
    } else if (y<0) {
        currentFrame=FindAnimationSetById("up");
    }
}

AnimationFrame* MultiAnimatedSprite::FindAnimationSetById(std::string id) {
    for(auto it=this->frames.begin(); it!=this->frames.end(); ++it) {
        if(it->first == id) {
            return (it->second);
        }
    }
    return NULL;
}
MultiAnimatedSprite::MultiAnimatedSprite(std::map<std::string,AnimationFrame*> frames, std::string defaultAnimationId):AnimatedSprite(NULL) {
    
    this->frames = frames;

    firstFrame=FindAnimationSetById(defaultAnimationId);
    currentFrame=firstFrame;

}
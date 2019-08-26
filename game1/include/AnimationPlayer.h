#include <AnimationFrame.h>

#ifndef ANIMATIONPLAYER_H
#define ANIMATIONPLAYER_H

class AnimationPlayer {
    private:
    AnimationFrame *firstFrame;

    public:
    AnimationPlayer(AnimationFrame* firstFrame);
}


#endif
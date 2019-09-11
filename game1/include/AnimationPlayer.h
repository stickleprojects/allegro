#include <AnimationFrame.h>

#ifndef ANIMATIONPLAYER_H_
#define ANIMATIONPLAYER_H_

class AnimationPlayer {
    private:
    AnimationFrame *firstFrame;

    public:
    explicit AnimationPlayer(AnimationFrame* firstFrame);
};


#endif  // ANIMATIONPLAYER_H_

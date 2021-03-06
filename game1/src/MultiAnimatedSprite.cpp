#include "MultiAnimatedSprite.h"

void MultiAnimatedSprite::Update() {
    // do nowt
    if (playAnimations) {
        AnimatedSprite::Update();
    } else {
        resetCurrentFrame();
    }
}
void MultiAnimatedSprite::resetCurrentFrame() {
    currentFrame = FindAnimationSetById(currentAnimationSetId);
    firstFrame = currentFrame;
}
void MultiAnimatedSprite::SetDirection(int x, int y) {
    SPDLOG_DEBUG("setting direction");

    if (x > 0) {
        currentFrame = FindAnimationSetById("right");
        currentAnimationSetId = "right";
    } else if (x < 0) {
        currentFrame = FindAnimationSetById("left");
        currentAnimationSetId = "left";
    } else if (y > 0) {
        currentFrame = FindAnimationSetById("down");
        currentAnimationSetId = "down";
    } else if (y < 0) {
        currentFrame = FindAnimationSetById("up");
        currentAnimationSetId = "up";
    }
    if (currentFrame == NULL) {
        currentFrame = FindAnimationSetById("right");
        currentAnimationSetId = "right";
    }
    if (x == 0 && y == 0) {
        playAnimations = false;
    } else {
        playAnimations = true;
    }
    SPDLOG_DEBUG("Direction %s", currentAnimationSetId);
    firstFrame = currentFrame;
    Sprite::SetDirection(x, y);
}

AnimationFrame *MultiAnimatedSprite::FindAnimationSetById(std::string id) {
    return this->animationSet->FindFirstFrameById(id);
}
MultiAnimatedSprite::MultiAnimatedSprite(AnimationSet *animationSet, std::string defaultAnimationId) : AnimatedSprite(NULL) {
    playAnimations = false;

    this->animationSet = animationSet;

    firstFrame = FindAnimationSetById(defaultAnimationId);
    currentFrame = firstFrame;
    currentAnimationSetId = defaultAnimationId;
}

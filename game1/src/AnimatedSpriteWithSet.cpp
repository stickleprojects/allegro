#include "AnimatedSpriteWithSet.h"


AnimatedSpriteWithSet::AnimatedSpriteWithSet (AnimationSet* animationSet): Sprite(NULL) {
    this->animationSet = animationSet;
}

void AnimatedSpriteWithSet::Update()
{
    // update the current frame and mvoe to next frame if needed
    animationSet->Update();
    
}
bool AnimatedSpriteWithSet::Draw()
{
    return Sprite::Draw();
    
    
}

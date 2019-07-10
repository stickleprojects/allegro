#include "AnimatedSprite.h"

bool AnimationFrame::IncrementFrameTime() {
    FrameTime++;
    if(FrameTime < FrameTimeMax) {
        return true;
    } else {
        FrameTime = 0;
        return false;
    }
}
void AnimatedSprite::Update() {
    if(!currentFrame->IncrementFrameTime()) {
        NextFrame();
    }
    
}

ALLEGRO_BITMAP* AnimatedSprite::GetImage() {
    if(!currentFrame) return NULL;

    return currentFrame->bitmap;
}

AnimatedSprite::~AnimatedSprite() {
    for(AnimationFrame* frame=firstFrame; frame; ) {
        AnimationFrame *n =frame->Next;
        delete frame;
        frame=n;
    }
}
AnimatedSprite::AnimatedSprite(ALLEGRO_BITMAP* images[], int numberOfFrames):Sprite(NULL) {
    firstFrame=NULL;
    AnimationFrame* tail = NULL;

    for(int i=0; i<numberOfFrames; i++) {
        if(images[i]) {
            AnimationFrame* current = new AnimationFrame();
            current->bitmap = images[i];
            current->FrameTimeMax=200;
            current->FrameTime=0;

            if(tail==NULL) {
                firstFrame = current;
            } else {
                tail->Next =current;

            }
            tail = current;

            printf("added animation frame %d\n", i);
            }
        else {
            printf("skipped missing image %d\n",i);
        }
        
    }
    currentFrame = firstFrame;


}

void AnimatedSprite::NextFrame() {
    currentFrame = currentFrame->Next;
    if(!currentFrame) currentFrame = firstFrame;

}
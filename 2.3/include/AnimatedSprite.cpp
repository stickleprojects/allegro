#include "AnimatedSprite.h"

bool AnimationFrame::IncrementFrameTime()
{
    FrameTime++;
    if (FrameTime < FrameTimeMax)
    {
        return true;
    }
    else
    {
        FrameTime = 0;
        return false;
    }
}
void AnimatedSprite::Update()
{
    printf("animationupdate %d/%d\n", currentFrame->FrameTime, currentFrame->FrameTimeMax);
    if (!currentFrame->IncrementFrameTime())
    {
        NextFrame();
    }
}
bool AnimatedSprite::Draw()
{
    ALLEGRO_BITMAP *image = this->GetImage();
    if (image)
    {
        if (scale == 1.0f)
        {
            al_draw_bitmap_region(image, currentFrame->Region.left, currentFrame->Region.top, currentFrame->Region.width, currentFrame->Region.height, X, Y, 0);
            // al_draw_bitmap(image, X, Y, 0);
        }
        else
        {
            al_draw_scaled_bitmap(image, currentFrame->Region.left, currentFrame->Region.top, currentFrame->Region.width, currentFrame->Region.height, X, Y, this->Width * this->scale, this->Height * this->scale, 0);
        }
    }
    return true;
}

ALLEGRO_BITMAP *AnimatedSprite::GetImage()
{
    if (!currentFrame)
        return NULL;

    return currentFrame->bitmap;
}

void AnimatedSprite::ClearFrames()
{
    if (framesOwnedByThis)
    {
        for (AnimationFrame *frame = firstFrame; frame;)
        {
            AnimationFrame *n = frame->Next;
            delete frame;

            frame = n;
        }
    }

    currentFrame = NULL;
    firstFrame = NULL;
}
AnimatedSprite::~AnimatedSprite()
{
    ClearFrames();
}

AnimatedSprite::AnimatedSprite(AnimationFrame* first):Sprite(NULL) {
    ClearFrames();
    firstFrame=first;
    framesOwnedByThis=false;
    currentFrame=firstFrame;
}

AnimatedSprite::AnimatedSprite(ALLEGRO_BITMAP *images[], int numberOfFrames) : Sprite(NULL)
{
    ClearFrames();
    AnimationFrame *tail = NULL;

    for (int i = 0; i < numberOfFrames; i++)
    {
        if (images[i])
        {
            AnimationFrame *current = new AnimationFrame();
            current->bitmap = images[i];
            current->FrameTimeMax = 2;
            current->FrameTime = 0;
            current->Region = Rect(0, 0, this->Width, this->Height);
            if (tail == NULL)
            {
                firstFrame = current;
            }
            else
            {
                tail->Next = current;
            }
            tail = current;

            printf("added animation frame %d\n", i);
        }
        else
        {
            printf("skipped missing image %d\n", i);
        }
    }
    currentFrame = firstFrame;
}


void AnimatedSprite::NextFrame()
{
    currentFrame = currentFrame->Next;
    if (!currentFrame)
        currentFrame = firstFrame;
}
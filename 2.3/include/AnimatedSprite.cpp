#include "AnimatedSprite.h"

void AnimatedSprite::NextFrame()
{
    SimpleAnimationFrame *saf = dynamic_cast<SimpleAnimationFrame *>(currentFrame);
    if (saf != NULL)
    {
        if (saf->Next)
        {
            currentFrame = saf->Next;
        }
        else
        {
            currentFrame = firstFrame;
        }
    }
}
void AnimatedSprite::Update()
{
    bool result = currentFrame->Update();

    if (!result)
    {
        NextFrame();
    }
}

void ASSERT_ISVALID (Rect r) {
assert (r.width > 0 && r.height>0 && r.left >=0 && r.top>=0);

}
bool AnimatedSprite::Draw()
{
    ALLEGRO_BITMAP *image = this->GetImage();
    if (image)
    {
        ASSERT_ISVALID (currentFrame->Region);
        //debug_print("drawing image %s", currentFrame->Id.c_str());

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
    if (framesOwnedByThis && firstFrame)
    {

        delete firstFrame;
    }

    currentFrame = NULL;
    firstFrame = NULL;
}
AnimatedSprite::~AnimatedSprite()
{
    ClearFrames();
}

AnimatedSprite::AnimatedSprite(AnimationFrame *first) : Sprite(NULL)
{
    ClearFrames();
    firstFrame = first;
    framesOwnedByThis = true;
    currentFrame = firstFrame;
}

AnimatedSprite::AnimatedSprite(ALLEGRO_BITMAP *images[], int numberOfFrames) : Sprite(NULL)
{
    ClearFrames();
    AnimationFrame *tail = NULL;

    firstFrame = new SimpleAnimationFrame("sa1", images, numberOfFrames, Rect(0, 0, this->Width, this->Height), 2);

    currentFrame = firstFrame;
}

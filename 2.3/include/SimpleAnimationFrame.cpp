#include "SimpleAnimationFrame.h"

bool SimpleAnimationFrame::Update()
{
    return IncrementFrameTime();
}
bool SimpleAnimationFrame::IncrementFrameTime()
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
SimpleAnimationFrame::SimpleAnimationFrame(std::string id, ALLEGRO_BITMAP *images[], int numberOfImages, Rect region, int frameTimeMax)
    : AnimationFrame(id)
{
    SimpleAnimationFrame *tail = NULL, *current = this;

    for (int i = 0; i < numberOfImages; i++)
    {
        if (images[i])
        {
            if (!tail)
            {
                this->bitmap = images[i];
                this->Region = region;
                this->FrameTimeMax = frameTimeMax;
                current = this;
            }
            else
            {
                std::string tempid = id + std::to_string(i);
                current = new SimpleAnimationFrame(tempid, images[i], region, frameTimeMax);

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
}

SimpleAnimationFrame::SimpleAnimationFrame(std::string id, ALLEGRO_BITMAP *bmp, Rect region, int frameTimeMax)
    : AnimationFrame(id, region)
{
    this->bitmap = bmp;
    this->FrameTimeMax = frameTimeMax;
    this->FrameTime = 0;
    this->Next = NULL;
}
void SimpleAnimationFrame::DeleteNext()
{
    if (this->Next)
    {
        printf("Chainging delete in the DeleteNext function\n");
        this->Next->DeleteNext();
        delete this->Next;
    }
}
SimpleAnimationFrame::~SimpleAnimationFrame()
{
    this->Next = NULL;
}
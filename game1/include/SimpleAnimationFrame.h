#include <string>
#include "AnimationFrame.h"

#ifndef SIMPLEANIMATIONFRAME_H_
#define SIMPLEANIMATIONFRAME_H_
class SimpleAnimationFrame : public AnimationFrame {
    int FrameTimeMax = 2;
    int FrameTime = 0;
    bool Update() override;
    bool IncrementFrameTime();
    ~SimpleAnimationFrame();

   public:
    SimpleAnimationFrame *Next = NULL;

    SimpleAnimationFrame(std::string id, ALLEGRO_BITMAP *images[], int numberOfImages, Rect region, int frameTimeMax);

    SimpleAnimationFrame(std::string id, ALLEGRO_BITMAP *bmp, Rect region, int frameTimeMax);

    void DeleteNext();
};

#endif  // SIMPLEANIMATIONFRAME_H_

#include "Sprite.h"
#include <string>

#ifndef ANIMATIONFRAME_H_
#define ANIMATIONFRAME_H_

struct Rect {
   public:
    float left, top, width, height;

   public:
    Rect(float l, float t, float w, float h) {
        left = l;
        top = t;
        width = w;
        height = h;
    }
    Rect() {
    }
};

class AnimationFrame {
   public:
    ALLEGRO_BITMAP *bitmap = NULL;
    Rect Region;
    std::string Id;
    virtual bool Update() { return false; }

    explicit AnimationFrame(std::string id) {
        assert(id.length() > 0);
        this->Id = id;
    }

    AnimationFrame(std::string id, Rect region) {
        assert(id.length() > 0);
        this->Id = id;
        Region = region;
    }
};

#endif  // ANIMATIONFRAME_H_

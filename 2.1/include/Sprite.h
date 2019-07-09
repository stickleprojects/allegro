#include "BitmapResource.h"
#include "Entity.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite:public Entity {
    private:
        BitmapResource *bmp;
        ALLEGRO_BITMAP* GetImage();

    public:
        Sprite(BitmapResource *res);
        bool Draw();
};

#endif

#include "BitmapResource.h"
#include "Entity.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite:public Entity {
    private:
        BitmapResource *bmp;
    protected:
        virtual ALLEGRO_BITMAP* GetImage();

    public:
        Sprite(BitmapResource *res);
        virtual void Update();
        virtual bool Draw();
};

#endif

#include "BitmapResource.h"
#include "Entity.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite:public Entity {
    private:
        BitmapResource *bmp;
    protected:
        virtual ALLEGRO_BITMAP* GetImage();
        int Width = 16;
        int Height = 16;

    public:
        float scale = 1.0f;
        
        Sprite(BitmapResource *res);
        virtual void Update();
        virtual bool Draw();
};

#endif

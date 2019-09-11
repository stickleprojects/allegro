#include "BitmapResource.h"
#include "Entity.h"

#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite : public Entity {
   private:
    BitmapResource *bmp;

   protected:
    virtual ALLEGRO_BITMAP *GetImage();

   public:
    int Width = 16;
    int Height = 16;
    int x_direction, y_direction;

    float scale = 1.0f;
    virtual void SetDirection(int x, int y);

    explicit Sprite(BitmapResource *res);
    virtual void Update();
    virtual bool Draw();
    virtual void Move();
    void SetDimensions(int w, int h);
};

#endif  // SPRITE_H_

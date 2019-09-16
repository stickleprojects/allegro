
#ifndef SPRITE_H_
#define SPRITE_H_

#include "BitmapResource.h"
#include "Entity.h"
#include "allegro5/allegro_color.h"

class Sprite : public Entity
{
private:
    BitmapResource *bmp;

protected:
    virtual ALLEGRO_BITMAP *GetImage();
    bool color_set = false;
    ALLEGRO_COLOR color;

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
    void SetColor(char r, char g, char b, char a);
    void SetColor(ALLEGRO_COLOR color);
    void SetDimensions(int w, int h);
};

#endif // SPRITE_H_

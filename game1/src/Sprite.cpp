#include "Sprite.h"

Sprite::Sprite(BitmapResource *resource)
{
    this->bmp = resource;
    X = 0;
    Y = 0;
}
void Sprite::SetColor(ALLEGRO_COLOR color) {
    this->color = color;
    color_set=true;
    
}
void Sprite::SetColor(char r, char g, char b, char a)
{
    color = al_map_rgba(r, g, b, a);
    if (r != 0 || g != 0 || b != 0 || a != 0)
    {
        color_set = true;
    }
    else
    {
        color_set = false;
    }
}
void Sprite::Move()
{
    if (x_direction != 0)
    {
        X += x_direction;
    }
    if (y_direction != 0)
    {
        Y += y_direction;
    }
}
void Sprite::SetDirection(int x, int y)
{
    // do nowt
    x_direction = x;
    y_direction = y;
}
ALLEGRO_BITMAP *Sprite::GetImage()
{
    return bmp->GetBitmap();
}
bool Sprite::Draw()
{
    ALLEGRO_BITMAP *image = this->GetImage();
    if (image)
    {
        if (scale == 1.0f)
        {
            if (color_set)
            {
                al_draw_tinted_bitmap(image, color, X, Y, 0);
            }
            else
            {
                al_draw_bitmap(image, X, Y, 0);
            }
        }
        else
        {
            if (color_set)
            {
                al_draw_tinted_scaled_bitmap(image, color, 0, 0, this->Width, this->Height, X, Y, this->Width * this->scale, this->Height * this->scale, 0);
            }
            else
            {
                al_draw_scaled_bitmap(image, 0, 0, this->Width, this->Height, X, Y, this->Width * this->scale, this->Height * this->scale, 0);
            }
        }
    }
    return true;
}
void Sprite::Update()
{
    this->X += 1;
}

void Sprite::SetDimensions(int w, int h)
{
    this->Width = w;
    this->Height = h;
}

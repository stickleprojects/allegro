#include "Sprite.h"

Sprite::Sprite(BitmapResource *resource) {
    this->bmp = resource;
    X=0;
    Y=0;
}

ALLEGRO_BITMAP* Sprite::GetImage() {
    return bmp->GetBitmap();
}
bool Sprite::Draw() {
    al_draw_bitmap(this->GetImage(), X, Y, 0);
    return true;
    
}

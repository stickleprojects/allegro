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
    ALLEGRO_BITMAP* image = this->GetImage();
    if(image) {
        al_draw_bitmap(image, X, Y, 0);
    }
    return true;
    
}
void Sprite::Update() {

}

#include "Sprite.h"

Sprite::Sprite(BitmapResource *resource) {
    this->bmp = resource;
    X=0;
    Y=0;
}

void Sprite::Move() {
    if(x_direction!=0) {
        X+= x_direction;
    }
    if(y_direction!=0) {
        Y += y_direction;
    }
}
void Sprite::SetDirection(int x, int y) {
    // do nowt
    x_direction = x;
    y_direction = y;

}
ALLEGRO_BITMAP* Sprite::GetImage() {
    return bmp->GetBitmap();
}
bool Sprite::Draw() {
    ALLEGRO_BITMAP* image = this->GetImage();
    if(image) {
        if(scale==1.0f) {
            al_draw_bitmap(image, X, Y, 0);
        } else {
            al_draw_scaled_bitmap (image, 0,0 , this->Width, this->Height, X, Y, this->Width*this->scale, this->Height*this->scale, 0  );
        }
    }
    return true;
    
}
void Sprite::Update() {
    this->X += 1;
}

void Sprite::SetDimensions (int w, int h) {
this->Width = w;
this->Height = h;

}

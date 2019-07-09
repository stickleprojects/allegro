#include "BitmapResource.h"

BitmapResource::BitmapResource(std::string relativePath, ALLEGRO_BITMAP* image) {
    assert(image);
    assert(relativePath.c_str());
    
    this->RelativePath = relativePath;
    
    this->bmp = image;
}
BitmapResource::~BitmapResource() {
   
}

std::string BitmapResource::GetRelativePath() {
    return RelativePath;
}
ALLEGRO_BITMAP* BitmapResource::GetBitmap() {
    
    return bmp;
}
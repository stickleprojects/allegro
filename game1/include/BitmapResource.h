#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <string>
#include "debug.h"

#ifndef BITMAP_RESOURCE_H
#define BITMAP_RESOURCE_H


class BitmapResource {
    private: 
        std::string RelativePath; 
        ALLEGRO_BITMAP *bmp;      
    public:
        operator ALLEGRO_BITMAP*()  {
            return bmp;
        }
        
        ~BitmapResource();
        BitmapResource(std::string relativePath, ALLEGRO_BITMAP *bitmap);
        ALLEGRO_BITMAP *GetBitmap();
       std::string GetRelativePath();
};

#endif

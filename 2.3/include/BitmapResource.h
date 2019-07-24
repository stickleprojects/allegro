#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <string>

#ifndef BITMAP_RESOURCE_H
#define BITMAP_RESOURCE_H


#define DEBUG 1

#define debug_print(fmt, ...) \
            do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

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

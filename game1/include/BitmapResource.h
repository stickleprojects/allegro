#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <string>

#ifndef BITMAPRESOURCE_H_
#define BITMAPRESOURCE_H_

class BitmapResource {
   private:
    std::string RelativePath;
    ALLEGRO_BITMAP *bmp;

   public:
    operator ALLEGRO_BITMAP *() {
        return bmp;
    }

    ~BitmapResource();
    BitmapResource(std::string relativePath, ALLEGRO_BITMAP *bitmap);
    ALLEGRO_BITMAP *GetBitmap();
    std::string GetRelativePath();
};

#endif  // BITMAPRESOURCE_H_

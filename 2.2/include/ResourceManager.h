#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <map>
#include <string>
#include <iterator>
#include "BitmapResource.h"

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

class ResourceManager {
    private: 
int bitmaps_loaded=0;
        std::map<std::string, BitmapResource*> resources;

    ALLEGRO_BITMAP* LoadBitmap(std::string path); 

  public:
    // ctor
    ResourceManager();
void Delete(BitmapResource *bmp);
    //dtor
    ~ResourceManager();
    void Clear();
BitmapResource* Get(std::string relativePath);
    BitmapResource* Add (std::string relativePath);
};

#endif
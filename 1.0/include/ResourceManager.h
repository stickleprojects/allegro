#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <map>
#include <string>
#include <iterator>

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

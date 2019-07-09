#include "ResourceManager.h"

#define DEBUG 1

ResourceManager::ResourceManager() {
    // ctor here 

}


ResourceManager::~ResourceManager() {
    // destroy managed resources
    Clear();
}

ALLEGRO_BITMAP* ResourceManager::LoadBitmap(std::string relativePath) {
    debug_print("loading bitmap #%d %s\n",bitmaps_loaded, relativePath.data());
    bitmaps_loaded++;

    return al_load_bitmap (relativePath.data());
}
void ResourceManager::Delete(BitmapResource *bmr) {
    al_destroy_bitmap(bmr->GetBitmap());
    bitmaps_loaded--;
debug_print("destroyed %s, bitmaps_remaining=%d\n", bmr->GetRelativePath().data(), bitmaps_loaded);
    
}
void ResourceManager::Clear() {
    // Iterate through all elements in std::map
    std::map<std::string, BitmapResource*>::iterator it = resources.begin();
    while(it != resources.end())
    {
        Delete(it->second);
        it++;
    }
}
BitmapResource* ResourceManager::Add(std::string relativePath) {
    ALLEGRO_BITMAP *bitmap = LoadBitmap(relativePath);
    BitmapResource* res =(BitmapResource*) new BitmapResource ( relativePath, bitmap);

    resources.insert (std::make_pair (relativePath, res));

return res;
}

BitmapResource* ResourceManager::Get(std::string relativePath) {
    return resources[relativePath];
}
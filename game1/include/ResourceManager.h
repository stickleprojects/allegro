#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <map>
#include <string>
#include <iterator>
#include "BitmapResource.h"
#include <dto.h>
#include <rpoco/json.hpp>

#include "spdlog.h"

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

class ResourceManager
{
private:
    int bitmaps_loaded = 0;
    std::map<std::string, BitmapResource *> resources;

    ALLEGRO_BITMAP *LoadBitmap(std::string path);

public:
    // ctor
    ResourceManager();
    void Delete(BitmapResource *bmp);
    //dtor
    ~ResourceManager();
    void Clear();
    BitmapResource *Get(std::string relativePath);
    BitmapResource *Add(std::string relativePath);

    template <class T>
    T LoadJsonDto(std::string filepath)
    {
        T dto;
        SPDLOG_INFO("Reading JsonDTO: {0}", filepath);

        std::ifstream is(filepath.c_str());
        if (rpoco::parse_json(is, dto))
        {
            SPDLOG_INFO("JsonDTO Read Ok\n {0}", rpoco::to_json(dto).c_str());
        }

        return dto;
    };
};

#endif
#include <string>
#include <vector>
#include "rpoco/json.hpp"

#ifndef PERSIST_INCLUDE_DTO_H_
#define PERSIST_INCLUDE_DTO_H_

struct PointDTO {
    int x = 0, y = 0;

    RPOCO(x, y);
};

struct FontDTO {
    std::string file;
    int size;
    int flags;

    RPOCO(file, size, flags);
};

struct HudDTO {
    FontDTO font;

    RPOCO(font);
};

struct LawnmowerDTO {
    std::vector<std::string> colorsRGBA;

    RPOCO(colorsRGBA)
};

struct ConfigDTO {
    PointDTO playerstart;
    HudDTO hud;

    LawnmowerDTO lawnmowers;

    RPOCO(playerstart, hud, lawnmowers);
};

struct RectDTO {
    int x = 0, y = 0, w = 0, h = 0;

    RPOCO(x, y, w, h);
};

struct AnimationFrameDTO {
    std::string id;
    RectDTO rect;
    std::string next;
    int frametimemax = 2;

    RPOCO(id, rect, next, frametimemax);
};

struct AnimationSetDTO {
    std::string id;
    std::vector<AnimationFrameDTO> frames;
    bool isDefault = false;

    RPOCO(id, frames, isDefault);
};

struct AnimationSetsDTO {
    std::vector<AnimationSetDTO> sets;
    std::string resource;

    RPOCO(sets, resource);

    AnimationSetDTO *GetDefaultSet() {
        for (auto i = sets.begin(); i != sets.end(); ++i) {
            if (i->isDefault) {
                return &(*i);
            }
        }
        return NULL;
    }
    AnimationSetDTO *FindSetById(std::string id) {
        for (auto i = sets.begin(); i != sets.end(); ++i) {
            if (i->id == id) {
                return &(*i);
            }
        }
        return NULL;
    }
};

#endif  // PERSIST_INCLUDE_DTO_H_

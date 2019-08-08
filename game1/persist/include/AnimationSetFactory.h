#include "SimpleAnimationFrame.h"
#include "dto.h"
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <spdlog.h>

#ifndef PERSIST_H
#define PERSIST_H


class AnimationSetFactory
{
public:
	AnimationFrame *create(ALLEGRO_BITMAP* bmp, AnimationSetDTO dto);
};


#endif

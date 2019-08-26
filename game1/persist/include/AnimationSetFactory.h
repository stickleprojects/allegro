
#ifndef PERSIST_H
#define PERSIST_H

#include "SimpleAnimationFrame.h"
#include "dto.h"
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <spdlog.h>

#include <AnimationSet.h>

/**
 * @brief Creates lists of animations keyed by id
 * 
 */
class AnimationSetFactory
{
public:
	AnimationFrame *create(ALLEGRO_BITMAP *bmp, AnimationSetDTO dto);
	AnimationSet *create(ALLEGRO_BITMAP *bmp, AnimationSetsDTO dto);
};

#endif

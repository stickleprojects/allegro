
#ifndef PERSIST_INCLUDE_ANIMATIONSETFACTORY_H_
#define PERSIST_INCLUDE_ANIMATIONSETFACTORY_H_


#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "Logging.h"
#include "SimpleAnimationFrame.h"
#include "dto.h"

#include <AnimationSet.h>

/**
 * @brief Creates lists of animations keyed by id
 * 
 */
class AnimationSetFactory {
   public:
    AnimationFrame *create(ALLEGRO_BITMAP *bmp, AnimationSetDTO dto);
    AnimationSet *create(ALLEGRO_BITMAP *bmp, AnimationSetsDTO dto);
};

#endif  // PERSIST_INCLUDE_ANIMATIONSETFACTORY_H_

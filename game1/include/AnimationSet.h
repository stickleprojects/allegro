
#ifndef ANIMATIONSET_H_
#define ANIMATIONSET_H_

#include <AnimationFrame.h>
#include <map>
#include <string>

/**
 * @brief Holds a collection of animation frames keyed on an id (ie. UP, DOWN, RIGHT)
 * 
 */
class AnimationSet {
   private:
    std::map<std::string, AnimationFrame *> frames;

   public:
    explicit AnimationSet(std::map<std::string, AnimationFrame *> frames);
    std::map<std::string, AnimationFrame *> GetFrames();
    AnimationFrame *FindFirstFrameById(std::string id);
};

#endif  // ANIMATIONSET_H_

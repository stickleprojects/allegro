
#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include <map>
#include <AnimationFrame.h>
#include <string>

/**
 * @brief Holds a collection of animation frames keyed on an id (ie. UP, DOWN, RIGHT)
 * 
 */
class AnimationSet
{
private:
	std::map<std::string, AnimationFrame *> frames;

public:
	AnimationSet(std::map<std::string, AnimationFrame *> frames);
	std::map<std::string, AnimationFrame *> GetFrames();
	AnimationFrame *FindFirstFrameById(std::string id);
};

#endif

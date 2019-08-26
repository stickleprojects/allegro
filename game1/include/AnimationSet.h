
#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include <map>
#include <AnimationFrame.h>
#include <string>

class AnimationSet
{
private:
	std::map<std::string, AnimationFrame *> frames;

public:
	AnimationSet(std::map<std::string, AnimationFrame *> frames);
	std::map<std::string, AnimationFrame *> GetFrames();
};

#endif

#include <AnimationSet.h>

AnimationSet::AnimationSet(std::map<std::string, AnimationFrame *> frames)
{
	this->frames = frames;
}
std::map<std::string, AnimationFrame *> AnimationSet::GetFrames()
{
	return this->frames;
}


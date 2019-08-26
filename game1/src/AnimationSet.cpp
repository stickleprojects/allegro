#include <AnimationSet.h>

AnimationFrame *AnimationSet::FindFirstFrameById(std::string id) {

    for (auto it = this->frames.begin(); it != this->frames.end(); ++it)
    {
        if (it->first == id)
        {
            return (it->second);
        }
    }
    return NULL;
}

AnimationSet::AnimationSet(std::map<std::string, AnimationFrame *> frames)
{
	this->frames = frames;
}
std::map<std::string, AnimationFrame *> AnimationSet::GetFrames()
{
	return this->frames;
}


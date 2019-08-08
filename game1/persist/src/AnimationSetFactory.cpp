#include "AnimationSetFactory.h"

std::map<std::string, AnimationFrame *> AnimationSetFactory::create(ALLEGRO_BITMAP *bmp, AnimationSetsDTO dto)
{

	std::map<std::string, AnimationFrame *> ret;

	for (auto it = dto.sets.begin(); it < dto.sets.end(); ++it)
	{
		auto *newFrame = this->create(bmp, *it);
		if (newFrame == NULL)
		{
			SPDLOG_ERROR("Failed to create frameset {0}", it->id);
			break;
		}
		ret.insert(std::make_pair( it->id, newFrame));
	}

	return ret;
}

AnimationFrame *AnimationSetFactory::create(ALLEGRO_BITMAP *bmp, AnimationSetDTO dto)
{
	std::map<std::string, SimpleAnimationFrame *> createdFrames;

	// create the frames first
	for (std::vector<AnimationFrameDTO>::iterator it = dto.frames.begin(); it != dto.frames.end(); ++it)
	{
		SimpleAnimationFrame *newFrame = new SimpleAnimationFrame(
			it->id,
			bmp,
			Rect(it->rect.x, it->rect.y, it->rect.w, it->rect.h),
			it->frametimemax);

		createdFrames[newFrame->Id] = newFrame;
	}
	// set up next pointers
	for (std::vector<AnimationFrameDTO>::iterator it = dto.frames.begin(); it != dto.frames.end(); ++it)
	{
		std::string nextId = it->next;

		SPDLOG_DEBUG("Connecting {0}=>{1}...", it->id.c_str(), nextId.c_str());

		if (nextId.empty())
		{
			SPDLOG_DEBUG("skipped");
		}
		else
		{
			std::map<std::string, SimpleAnimationFrame *>::iterator foundNext = createdFrames.find(nextId);
			std::map<std::string, SimpleAnimationFrame *>::iterator foundCurrent = createdFrames.find(it->id);

			if (foundNext == createdFrames.end())
			{
				SPDLOG_DEBUG("Failed to find next");
			}
			else
			{
				// found one!
				if (foundCurrent == createdFrames.end())
				{
					SPDLOG_DEBUG("Failed to find current");
				}
				else
				{
					SPDLOG_DEBUG("Ok");
					foundCurrent->second->Next = foundNext->second;
				}
			}
		}
	}

	return createdFrames.begin()->second;
}

#include "AnimationSetFactory.h"

AnimationFrame* AnimationSetFactory::create(ALLEGRO_BITMAP* bmp, AnimationSetDTO dto) {
	std::map<std::string, SimpleAnimationFrame*> createdFrames;

	// create the frames first
	for(std::vector<AnimationFrameDTO>::iterator it=dto.frames.begin(); it!=dto.frames.end(); ++it) {
		SimpleAnimationFrame* newFrame = new SimpleAnimationFrame (
			it->id,
			bmp, 
			Rect(it->rect.x, it->rect.y, it->rect.w, it->rect.h),
			it->frametimemax);

		createdFrames[newFrame->Id] = newFrame;
	}
	// set up next pointers
	for(std::vector<AnimationFrameDTO>::iterator it=dto.frames.begin(); it!=dto.frames.end(); ++it) {
		std::string nextId = it->next;
		std::map<std::string, SimpleAnimationFrame*>::iterator foundNext = createdFrames.find(nextId);
		std::map<std::string, SimpleAnimationFrame*>::iterator foundCurrent = createdFrames.find(it->id);
		
		if(foundNext == createdFrames.end()) {
			printf("Failed to find next %s", nextId.c_str());
		} else {
			// found one!
			if(foundCurrent == createdFrames.end()) {
				printf("Failed to find current %s", it->id.c_str());
			} else {
				foundCurrent->second->Next = foundNext->second;
			}
		}
	}
	return NULL;

}

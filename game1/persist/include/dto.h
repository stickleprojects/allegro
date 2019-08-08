#include "rpoco/json.hpp"

#ifndef DTO
#define DTO

struct RectDTO
{
	int x = 0, y = 0, w = 0, h = 0;

	RPOCO(x, y, w, h);
};

struct AnimationFrameDTO
{
	std::string id;
	RectDTO rect;
	std::string next;
	int frametimemax = 2;

	RPOCO(id, rect, next, frametimemax);
};

struct AnimationSetDTO
{
	std::string id;
	std::vector<AnimationFrameDTO> frames;

	RPOCO(id, frames);
};

struct AnimationSetsDTO
{
	std::vector<AnimationSetDTO> sets;
	std::string resource;

	RPOCO(sets, resource);

	bool FindById(std::string id, AnimationSetDTO *dto) {
		for(auto i = sets.begin(); i!=sets.end(); ++i) {
			if(i -> id == id) {
				dto = &(*i);
				return true;
			}
		}
		return false;
	}
};

#endif

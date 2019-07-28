// https://github.com/whizzter/rpoco
#include "rpoco/json.hpp"
#include <vector>
#include <string>
#include "SimpleAnimationFrame.h"
#include "dto.h"
#include "AnimationSetFactory.h"

struct Simple
{
	std::string hello;
	int x = 0;

	RPOCO(hello, x);
};

int test_animationsets_poco() {
	AnimationSetsDTO dto;

	std::ifstream is("resources//animationsetsdto.json");
	if (rpoco::parse_json(is, dto)) {
		printf("Ok\n %s\n", rpoco::to_json(dto).c_str());

	ALLEGRO_BITMAP *bmp = NULL;

		AnimationSetFactory* factory = new AnimationSetFactory();
		AnimationFrame* frame= factory->create(bmp,dto.sets.front());
		delete factory;

	}
return 0;
}
int test_animationframe_poco() {
	AnimationFrameDTO dto;

	std::ifstream is("resources//animationframedto.json");
	if (rpoco::parse_json(is, dto)) {
		printf("Ok\n %s\n", rpoco::to_json(dto).c_str());
	}
return 0;
}
int test_rpoco() {
    // declare structure
	Simple data;

	// sample data
	std::string sampleText="{ \"hello\":\"world\"  ,  \"x\":123  }";

	// parse in data
	rpoco::parse_json(sampleText,data);
	
	// now write the data from the object back to a new json string
	std::string outputText=rpoco::to_json(data);

	// and print it
	printf("%s\n",outputText.c_str());

	return 0;
}


#include "main.h"
#include "rpoco_demo.h"


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

int dogame() {
    Game game;

    return game.GameMain();

}
int main()
{

//return dogame();
   return test_rpoco();

}
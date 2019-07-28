// https://github.com/whizzter/rpoco
#include "rpoco/json.hpp"

struct Simple {
	std::string hello;
	int x=0;

	RPOCO(hello,x);
};

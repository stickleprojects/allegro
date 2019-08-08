#include "main.h"
#include "rpoco_demo.h"
#include <fstream>
#include <map>



int dogame() {
    Game game;

    return game.GameMain();

}
int main()
{
spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
    
return dogame();
   //return test_animationsets_poco();

}
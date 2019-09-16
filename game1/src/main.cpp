#include "main.h"

int dogame() {
    Game game;

    return game.GameMain();
}
int main() {
    
    spdlog::set_level(spdlog::level::trace);

    SPDLOG_INFO("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
SPDLOG_DEBUG("Debugging on");

    return dogame();
    // return test_animationsets_poco();
}

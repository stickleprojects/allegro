#ifndef GAME_H
#define GAME_H

#include "spdlog.h"
#include "MultiAnimatedSprite.h"

#include "ResourceManager.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "AnimationFrame.h"
#include "SimpleAnimationFrame.h"
#include <vector>
#include <string>
#include <dto.h>
#include <AnimationSetFactory.h>

#define SCREENW 1024 * 2 // 640
#define SCREENH 960 * 2  //480
#define CAMERA_X 0
#define CAMERA_Y 0
#define CAMERA_SCALE 2.0f
#define PLAYER_SPEED 5

#define BACKGROUND_IMAGE "resources/background.png"

struct POINT
{
    int x;
    int y;

    POINT(int theX, int theY)
    {
        this->x = theX;
        this->y = theY;
    }
};

enum GameStateEnum
{
    Playing,
    Quit
};

struct VECTOR
{
    int X = 0;
    int Y = 0;

    VECTOR(int x, int y)
    {
        X = x;
        Y = y;
    }
};

class Game
{
private:
    GameStateEnum GameState = GameStateEnum::Playing;
    VECTOR PlayerMovement = VECTOR(0, 0);

    ALLEGRO_FONT *font = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_DISPLAY *disp = NULL;
    ResourceManager *rm = NULL;
    Sprite *player = NULL;

    POINT cameraPosition = POINT(0, 0);
    ALLEGRO_TRANSFORM camera;
    float cameraScale = CAMERA_SCALE;

    ConfigDTO config;
    int cameraX = CAMERA_X;
    int cameraY = CAMERA_Y;
    AnimationFrame *first = NULL;

    void moveSprite(Sprite *sprite);
    int init();
    GameStateEnum handleInput(GameStateEnum existingState);

    int initResources();
    int initConfig();
    bool updateCamera();
    void drawBackground();
    void drawSprites();
    void updateNextPointers(std::vector<AnimationFrame *> tgt);
    void initSprites();
    void initPlayer(std::string animationsFilepath);
    void drawHud();

public:
    ~Game();
    int GameMain();
};

#endif

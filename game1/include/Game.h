#ifndef GAME_H
#define GAME_H

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
#define CAMERA_SCALE 3.0f

#define BACKGROUND_IMAGE "resources/background.png"

class Game
{
private:
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_DISPLAY *disp = NULL;
    ResourceManager *rm = NULL;
    Sprite *player = NULL;

    POINT cameraPosition = POINT(0, 0);
    ALLEGRO_TRANSFORM camera;
    float cameraScale = CAMERA_SCALE;

    int cameraX = CAMERA_X;
    int cameraY = CAMERA_Y;
    AnimationFrame *first = NULL;

    void moveSprite(Sprite *sprite);
    int init();

    int initResources();
    bool updateCamera();
    void drawBackground();
    void drawSprites();
    void updateNextPointers(std::vector<AnimationFrame *> tgt);
    void initSprites();

    
public:
~Game();
    int GameMain();
};

#endif

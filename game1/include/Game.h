#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <vector>

#include "MultiAnimatedSprite.h"
#include "Logging.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "AnimatedSprite.h"
#include "AnimationFrame.h"
#include "ResourceManager.h"
#include "SimpleAnimationFrame.h"
#include "StringFormat.h"

#include "Sprite.h"
#include "Spawner.h"
#include "Spawners/LawnmowerSpawner.h"
#include "AnimationSetFactory.h"
#include "VectorFuncs.h"
#include "dto.h"

#define SCREENW 1024 * 1  // 640
#define SCREENH 960 * 1   // 480
#define MIN_X -100
#define MAX_X 500

#define CAMERA_X 0
#define CAMERA_Y 0
#define CAMERA_SCALE 2.0f
#define PLAYER_SPEED 5

#define BACKGROUND_IMAGE "resources/background.png"

struct POINT {
    int x;
    int y;

    POINT(int theX, int theY) {
        this->x = theX;
        this->y = theY;
    }
};

enum GameStateEnum {
    Playing,
    Quit
};

struct VECTOR {
    int X = 0;
    int Y = 0;

    VECTOR(int x, int y) {
        X = x;
        Y = y;
    }
};

class Game {
   private:
    GameStateEnum GameState = GameStateEnum::Playing;
    VECTOR PlayerMovement = VECTOR(0, 0);

    double FPS = 0;
    double old_time;
    void updateFPS();

    ALLEGRO_FONT *font = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_DISPLAY *disp = NULL;
    ResourceManager *rm = NULL;
    Sprite *player = NULL;
    std::vector<Sprite *> npcs;
    std::vector<Spawner*> spawners;
    void initLawnmowerSpawner();
    void initSpawners();
    void updateSpawners();

    Sprite *CreateNPC(std::string animationsFilePath, int startX, int startY, int directionX);

    POINT cameraPosition = POINT(0, 0);
    ALLEGRO_TRANSFORM camera;
    float cameraScale = CAMERA_SCALE;
    bool isOffScreen(Sprite *sprite);
    void updateNPCs();
    Sprite *CreateLawnmowerSprite(int x, int y, int directionX);
    ConfigDTO config;
    int cameraX = CAMERA_X;
    int cameraY = CAMERA_Y;
    AnimationFrame *first = NULL;

    void moveSprite(Sprite *sprite);
    int init();
    GameStateEnum handleInput(GameStateEnum existingState);
    void initNPCs();

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

#endif  //  GAME_H_

/**
 * Copyright 2019 Kieron Wray
 * 
 **/

#include "Game.h"

void Game::moveSprite(Sprite *sprite)
{
    sprite->X += PlayerMovement.X;
    sprite->Y += PlayerMovement.Y;
    sprite->SetDirection(PlayerMovement.X, PlayerMovement.Y);

    SPDLOG_DEBUG("moved player {0},{1}", sprite->X, sprite->Y);
    PlayerMovement = VECTOR(0, 0);

    for (auto npc : npcs)
    {
        npc->Move();
    }
}

int Game::init()
{
    if (!al_init())
    {
        SPDLOG_ERROR("couldn't initialize allegro\n");
        return 1;
    }

    if (!al_init_image_addon())
    {
        SPDLOG_ERROR("couldn't initialize image addon\n");
        return 1;
    }

    if (!al_install_keyboard())
    {
        SPDLOG_ERROR("couldn't initialize keyboard\n");
        return 1;
    }
    if (!al_init_font_addon())
    {
        SPDLOG_ERROR("couldn't intialize font\n");
        return 1;
    }
    if (!al_init_ttf_addon())
    {
        SPDLOG_ERROR("couldn't intialize ttf\n");
        return 1;
    }
    timer = al_create_timer(1.0 / 30.0);
    if (!timer)
    {
        SPDLOG_ERROR("couldn't initialize timer\n");
        return 1;
    }

    queue = al_create_event_queue();
    if (!queue)
    {
        SPDLOG_ERROR("couldn't initialize queue\n");
        return 1;
    }

    // al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    disp = al_create_display(SCREENW, SCREENH);
    if (!disp)
    {
        SPDLOG_ERROR("couldn't initialize display");
        return 1;
    }
    SPDLOG_INFO("font {0}", config.hud.font.file.c_str());

    font = al_load_ttf_font(config.hud.font.file.c_str(), config.hud.font.size, config.hud.font.flags);
    if (!font)
    {
        SPDLOG_ERROR("couldn't load font: {0}", config.hud.font.file);
        return 1;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    return 0;
}
int Game::initResources()
{
    rm = reinterpret_cast<ResourceManager *>(new ResourceManager());

    rm->Add(BACKGROUND_IMAGE);

    SPDLOG_INFO("resources loaded\n");

    return 0;
}
bool Game::updateCamera()
{
    if (cameraX < 0)
        cameraX = 0;
    if (cameraY < 0)
        cameraY = 0;

    return true;
}
void Game::drawBackground()
{
    static ALLEGRO_BITMAP *backgroundCachedImage = NULL;

    if (backgroundCachedImage == NULL)
    {
        SPDLOG_INFO("caching background image");
        BitmapResource *res = rm->Get(BACKGROUND_IMAGE);
        backgroundCachedImage = res->GetBitmap();
    }
    al_draw_bitmap(backgroundCachedImage, 0, 0, 1);
}
void Game::drawHud()
{
    auto s = stringFormat("FPS %d Player (%d,%d)", static_cast<int>(FPS), player->X, player->Y);
    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, s.c_str());

    int y = 0;
    int x = 200;
    int gap = 10;

    for (auto spwn : spawners)
    {
        auto txt = spwn->ToString();
        al_draw_text(font, al_map_rgb(255, 255, 255), x, y, ALLEGRO_ALIGN_LEFT, txt.c_str());

        y += gap;
    }
}
void Game::drawSprites()
{
    drawHud();
    try
    {
        player->Update();

        player->Draw();

        for (auto nps : npcs)
        {
            nps->Draw();
        }
    }
    catch (std::runtime_error &e)
    {
        SPDLOG_ERROR("Error during draw %s", e.what());
    }
}

void Game::updateNextPointers(std::vector<AnimationFrame *> tgt)
{
    SimpleAnimationFrame *prev = NULL;
    for (auto it = tgt.begin(); it != tgt.end(); ++it)
    {
        auto *saf = dynamic_cast<SimpleAnimationFrame *>((*it));

        if (saf)
        {
            if (prev)
            {
                prev->Next = saf;
            }
            prev = saf;
        }
    }
}
void Game::initPlayer(std::string animationsFilepath)
{
    auto dto = rm->LoadJsonDto<AnimationSetsDTO>(animationsFilepath);

    rm->Add(dto.resource);
    auto *spritesheet = rm->Get(dto.resource);

    auto factory = new AnimationSetFactory();

    auto animationSet = factory->create(spritesheet->GetBitmap(), dto);

    auto defaultAnimation = dto.GetDefaultSet();
    if (defaultAnimation == NULL)
    {
        auto firstOne = dto.sets.begin();
        defaultAnimation = &(*firstOne);
    }

    player = new MultiAnimatedSprite(animationSet, defaultAnimation->id);
    player->scale = CAMERA_SCALE;
    player->X = config.playerstart.x;
    player->Y = config.playerstart.y;
}
Sprite *Game::CreateNPC(std::string animationsFilepath, int startX, int startY, int directionX, ALLEGRO_COLOR color)
{
    auto dto = rm->LoadJsonDto<AnimationSetsDTO>(animationsFilepath);

    rm->Add(dto.resource);
    auto *spritesheet = rm->Get(dto.resource);

    auto factory = new AnimationSetFactory();

    auto animationSet = factory->create(spritesheet->GetBitmap(), dto);

    auto defaultAnimation = dto.GetDefaultSet();
    if (defaultAnimation == NULL)
    {
        auto firstOne = dto.sets.begin();
        defaultAnimation = &(*firstOne);
    }

    auto npc = new MultiAnimatedSprite(animationSet, defaultAnimation->id);
    npc->scale = CAMERA_SCALE;
    npc->X = startX;
    npc->Y = startY;

    npc->SetColor(color);

    npc->SetDirection(directionX, 0);

    // set dims from teh first frame
    auto firstFrame = defaultAnimation->frames.begin();
    npc->SetDimensions(firstFrame->rect.w, firstFrame->rect.h);

    return npc;
}
Sprite *Game::CreateLawnmowerSprite(ALLEGRO_COLOR color, int x, int y, int directionX)
{
    std::string animationsFilepath = "resources/np1animations.json";

    return CreateNPC(animationsFilepath, x, y, directionX, color);
}

void Game::initSprites()
{
    initPlayer("resources/playeranimations.json");
}

Game::~Game()
{
    SPDLOG_DEBUG("Destroying game");
    npcs.clear();

    if (font)
    {
        al_destroy_font(font);
        font = NULL;
    }
    if (disp)
    {
        al_destroy_display(disp);
        disp = NULL;
    }
    if (timer)
    {
        al_destroy_timer(timer);
        timer = NULL;
    }
    if (queue)
    {
        al_destroy_event_queue(queue);
        queue = NULL;
    }
    if (rm)
    {
        delete rm;
        rm = NULL;
    }
}

GameStateEnum Game::handleInput(GameStateEnum existingState)
{
    ALLEGRO_KEYBOARD_STATE keyboardState;
    al_get_keyboard_state(&keyboardState);

    if (al_key_down(&keyboardState, ALLEGRO_KEY_RIGHT))
    {
        PlayerMovement = VECTOR(PLAYER_SPEED, 0);
    }
    if (al_key_down(&keyboardState, ALLEGRO_KEY_LEFT))
    {
        PlayerMovement = VECTOR(-1 * PLAYER_SPEED, 0);
    }
    if (al_key_down(&keyboardState, ALLEGRO_KEY_UP))
    {
        PlayerMovement = VECTOR(0, -1 * PLAYER_SPEED);
    }
    if (al_key_down(&keyboardState, ALLEGRO_KEY_DOWN))
    {
        PlayerMovement = VECTOR(0, PLAYER_SPEED);
    }
    if (al_key_down(&keyboardState, ALLEGRO_KEY_ESCAPE))
    {
        return GameStateEnum::Quit;
    }

    return existingState;
}
int Game::initConfig()
{
    config = rm->LoadJsonDto<ConfigDTO>("resources/configdto.json");

    return 0;
}
void Game::updateFPS()
{
    double new_time = al_get_time();
    double delta = new_time - old_time;
    FPS = 1 / delta;
    old_time = new_time;
}
std::vector<ALLEGRO_COLOR> Game::createColorsFromRGBAStrings(std::vector<std::string> data)
{
    std::vector<ALLEGRO_COLOR> ret;
    for (auto hexCode : data)
    {
        // convert string to upper case
        std::for_each(hexCode.begin(), hexCode.end(), [](char &c) {
            c = ::toupper(c);
        });
        // split string into tokens
        // ... and extract the rgb values.
        uint r, g, b, a;

        std::istringstream(hexCode.substr(0, 2)) >> std::hex >> r;
        std::istringstream(hexCode.substr(2, 2)) >> std::hex >> g;
        std::istringstream(hexCode.substr(4, 2)) >> std::hex >> b;
        a = 255;
        // alpha defaults to 255
        // if (hexCode.length() > 6)
        // {
        //     std::istringstream(hexCode.substr(6, 2)) >> std::hex >> a;
        // }
        SPDLOG_DEBUG("{0}=argb({1},{2},{3},{4})", hexCode, r, g, b, a);
        ret.push_back(al_map_rgba(r, g, b, a));
    }
    return ret;
}
void Game::initLawnmowerSpawner()
{
    auto lawnmowerColors = createColorsFromRGBAStrings(config.lawnmowers.colorsRGBA);
    ALLEGRO_COLOR *lmc_array = lawnmowerColors.data();

    auto sp = new LawnmowerSpawner(MIN_X, MAX_X, [=](int x, int y, int direction) {
        ALLEGRO_COLOR c = lmc_array[(y - 320) % 32];
        npcs.push_back(CreateLawnmowerSprite(c, x, y, direction));
    });

    spawners.push_back(sp);
}
void Game::initSpawners()
{
    initLawnmowerSpawner();

    // force immediate spawn
    for (auto s : spawners)
    {
        s->Spawn();
    }
}
bool Game::isOffScreen(Sprite *sprite)
{
    return (sprite->X + sprite->Width < MIN_X) || (sprite->X > MAX_X);
}
void Game::updateSpawners()
{
    for (auto s : spawners)
    {
        s->Update();
    }
}
void Game::updateNPCs()
{
    for (auto nps : npcs)
    {
        nps->Update();

        // kill any offscreen
        if (isOffScreen(nps))
        {
            DeleteFromVector(npcs, nps);
        }
    }
}
int Game::GameMain()
{
    if (initConfig() != 0)
    {
        return 1;
    }

    if (init() != 0)
    {
        return 1;
    }

    if (initResources() != 0)
    {
        return 2;
    }

    initSprites();
    initSpawners();

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    double old_time = al_get_time();

    while (GameState == GameStateEnum::Playing)
    {
        updateFPS();

        GameState = handleInput(GameState);

        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            moveSprite(player);
            updateNPCs();
            updateSpawners();
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            SPDLOG_DEBUG(event);
            GameState = GameStateEnum::Quit;

            break;
        }

        if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // create a 00 transform
            al_identity_transform(&camera);
            // move the cam
            al_translate_transform(&camera, cameraPosition.x, cameraPosition.y);
            al_scale_transform(&camera, cameraScale, cameraScale);

            al_use_transform(&camera);

            drawBackground();

            drawSprites();

            al_flip_display();

            redraw = false;
        }
    }

    return 0;
}

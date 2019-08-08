#include "Game.h"

void Game::moveSprite(Sprite *sprite)
{
    sprite->X += 0;
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

    font = al_create_builtin_font();
    if (!font)
    {
        SPDLOG_ERROR("couldn't initialize font");
        return 1;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    return 0;
}
int Game::initResources()
{
    rm = (ResourceManager *)new ResourceManager();

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
void Game::drawSprites()
{
    al_draw_text(font, al_map_rgb(255, 255, 255), 100, 10, ALLEGRO_ALIGN_RIGHT, "Hello world!");
    player->Update();

    player->Draw();
}

void Game::updateNextPointers(std::vector<AnimationFrame *> tgt)
{
    SimpleAnimationFrame *prev = NULL;
    for (std::vector<AnimationFrame *>::iterator it = tgt.begin(); it != tgt.end(); ++it)
    {
        SimpleAnimationFrame *saf = dynamic_cast<SimpleAnimationFrame *>((*it));

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
void Game::initSprites()
{
    //player = new Sprite(rm->Get("resources/mysha.png"));
    AnimationSetsDTO dto;
    std::string filepath = "resources/animationsetsdto.json";

    dto = rm->LoadJsonDto<AnimationSetsDTO>(filepath);

    rm->Add("resources/spritesheet1.png");
    BitmapResource *spritesheet = rm->Get("resources/spritesheet1.png");

    auto factory = new AnimationSetFactory();
    auto firstFrame = factory->create(spritesheet->GetBitmap(), dto.sets[0]);

    player = new AnimatedSprite(firstFrame);
    player->scale = CAMERA_SCALE;
}

Game::~Game()
{
    SPDLOG_DEBUG("Destroying game");
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

int Game::GameMain()
{
    if (init() != 0)
    {
        return 1;
    }

    if (initResources() != 0)
    {
        return 2;
    }

    initSprites();

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    while (1)
    {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            moveSprite(player);
        }
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

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
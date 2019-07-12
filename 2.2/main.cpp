#include "include/ResourceManager.h"
#include "include/Sprite.h"
#include "include/AnimatedSprite.h"
#include <vector>
#include <string>
#define DEBUG 11

ALLEGRO_FONT *font = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;
ALLEGRO_DISPLAY *disp = NULL;
ResourceManager *rm = NULL;
Sprite *player = NULL;

#define SCREENW 1024*2 // 640
#define SCREENH 960*2 //480
#define CAMERA_X 0
#define CAMERA_Y 0
#define CAMERA_SCALE 3.0f

#define BACKGROUND_IMAGE "resources/background.png"
struct POINT {
    int x;
    int y;

    POINT(int theX, int theY) {
        this->x = theX;
        this->y = theY;
    }
};

POINT cameraPosition= POINT(0,0);
ALLEGRO_TRANSFORM camera;
float cameraScale = CAMERA_SCALE;

void moveSprite(Sprite *sprite)
{
    sprite->X += 0;
    
}

int init()
{
    if (!al_init())
    {
        printf("couldn't initialize allegro\n");
        return 1;
    }

    if (!al_init_image_addon())
    {
        printf("couldn't initialize image addon\n");
        return 1;
    }

    if (!al_install_keyboard())
    {
        printf("couldn't initialize keyboard\n");
        return 1;
    }

    timer = al_create_timer(1.0 / 30.0);
    if (!timer)
    {
        printf("couldn't initialize timer\n");
        return 1;
    }

    queue = al_create_event_queue();
    if (!queue)
    {
        printf("couldn't initialize queue\n");
        return 1;
    }

    // al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    disp = al_create_display(SCREENW, SCREENH);
    if (!disp)
    {
        printf("couldn't initialize display\n");
        return 1;
    }

    font = al_create_builtin_font();
    if (!font)
    {
        printf("couldn't initialize font\n");
        return 1;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    return 0;
}
int initResources()
{
    rm = (ResourceManager *)new ResourceManager();

    rm->Add(BACKGROUND_IMAGE);
    rm->Add("resources/mysha.png");

    printf("resources loaded\n");

    return 0;
}
int cameraX = CAMERA_X;
int cameraY = CAMERA_Y;
bool updateCamera() {
    if(cameraX<0) cameraX=0;
    if (cameraY<0) cameraY=0;

return true;
}
void DrawBackground()
{
    static ALLEGRO_BITMAP *backgroundCachedImage = NULL;

    if (backgroundCachedImage == NULL)
    {
        printf("caching background image\n");
        BitmapResource *res = rm->Get(BACKGROUND_IMAGE);
        backgroundCachedImage = res->GetBitmap();
    }
    al_draw_bitmap(backgroundCachedImage, 0, 0, 1);
}
void DrawSprites()
{
    al_draw_text(font, al_map_rgb(255, 255, 255), 100, 10, ALLEGRO_ALIGN_RIGHT, "Hello world!");
    player->Update();

    player->Draw();
}
void initSprites()
{
    //player = new Sprite(rm->Get("resources/mysha.png"));
    std::vector<ALLEGRO_BITMAP *> cells;

    for (int i = 1; i <= 5; i++)
    {

        std::string filepath = "resources/player" + std::to_string(i) + ".png";
        printf("loading sprite image %s\n", filepath.c_str());
        rm->Add(filepath.c_str());
        BitmapResource *bmp = rm->Get(filepath.c_str());

        cells.push_back(bmp->GetBitmap());
    }

    printf("here\n");

    player = new AnimatedSprite(&cells[0], cells.size());
    player->scale = CAMERA_SCALE;
}
int main()
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
            al_translate_transform (&camera,cameraPosition.x, cameraPosition.y);
            al_scale_transform(&camera, cameraScale, cameraScale);

            al_use_transform(&camera);

            DrawBackground();

            DrawSprites();


            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    delete rm;
}
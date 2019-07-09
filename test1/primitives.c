// https://github.com/liballeg/allegro_wiki/wiki/Allegro-Vivace%3A-Graphics

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

void must_init(bool result, char* msg) {
    if(!result) {
        printf("Couldn't initialize %s", msg);
        exit(1);
    }
}

int main()
{
    must_init(al_init(),"allegro");
       
must_init(al_init_image_addon(),"images");

    must_init(al_install_keyboard(),"keyboard");
    must_init(al_init_primitives_addon(), "primitives");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    if(!timer)
    {
        printf("couldn't initialize timer\n");
        return 1;
    }

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    if(!queue)
    {
        printf("couldn't initialize queue\n");
        return 1;
    }

    ALLEGRO_DISPLAY* disp = al_create_display(1024, 640);
    if(!disp)
    {
        printf("couldn't initialize display\n");
        return 1;
    }

    ALLEGRO_FONT* font = al_create_builtin_font();
    if(!font)
    {
        printf("couldn't initialize font\n");
        return 1;
    }
    ALLEGRO_BITMAP* mysha = al_load_bitmap("resources/mysha.png");
    if(!mysha) {
        printf("couldnt load mysha\n");
        return 1;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event;
    
    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

int x = 300;
int y = 100;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), x, y, ALLEGRO_ALIGN_RIGHT, "Hello world!");
            al_draw_bitmap(mysha, 200, 200, 0);

            al_draw_filled_triangle(35, 350, 85, 375, 35, 400, al_map_rgb_f(0, 1, 0));
            al_draw_filled_rectangle(240, 260, 340, 340, al_map_rgba_f(0, 0, 0.5, 0.5));
            al_draw_circle(450, 370, 30, al_map_rgb_f(1, 0, 1), 2);
            al_draw_line(440, 110, 460, 210, al_map_rgb_f(1, 0, 0), 1);
            al_draw_line(500, 220, 570, 200, al_map_rgb_f(1, 1, 0), 1);

ALLEGRO_VERTEX v[] = {
    { .x = 210, .y = 320, .z = 0, .color = al_map_rgb_f(1, 0, 0) },
    { .x = 330, .y = 320, .z = 0, .color = al_map_rgb_f(0, 1, 0) },
    { .x = 210, .y = 420, .z = 0, .color = al_map_rgb_f(0, 0, 1) },
    { .x = 330, .y = 420, .z = 0, .color = al_map_rgb_f(1, 1, 0) },
};

al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_STRIP);
            al_flip_display();

            redraw = false;
        }
    }

al_destroy_bitmap(mysha);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <allegro5/allegro_image.h>
#include <stdio.h>


int main()
{   
    if(!al_init()) {
        printf("couldn't initialize allegro\n");
        return 1;
    }

if(!al_init_image_addon())
{
    printf("couldn't initialize image addon\n");
    return 1;
}

    if(!al_install_keyboard())
    {
        printf("couldn't initialize keyboard\n");
        return 1;
    }

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
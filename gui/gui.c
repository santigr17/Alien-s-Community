#include "gui.h"


//allegro variable
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *path = NULL;
// 
//

bool done = false;
bool render = false;	
#define EXIT_COUNT 11
#define ENTRANCE_COUNT 13
#define AVENUE_COUNT 30

struct PATH alfaexit[EXIT_COUNT];
struct PATH alfaentrance[ENTRANCE_COUNT];
struct PATH northavenue[AVENUE_COUNT];

struct PATH betaexit[EXIT_COUNT];
struct PATH betaentrance[ENTRANCE_COUNT];
struct PATH southavenue[AVENUE_COUNT];




void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}
/**
*/
int init_gui(GUI_CONTEXT *ctx)
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ctx->timer = al_create_timer(1.0 / 30.0);
    must_init(ctx->timer, "timer");

    ctx->queue = al_create_event_queue();
    must_init(ctx->queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    ctx->disp = al_create_display(975, 678);
    must_init(ctx->disp, "display");

    ctx->font = al_create_builtin_font();
    must_init(ctx->font, "font");

    set_background(ctx);

    must_init(al_init_primitives_addon(), "primitives");
    al_register_event_source(ctx->queue, al_get_keyboard_event_source());
    al_register_event_source(ctx->queue, al_get_display_event_source(ctx->disp));
    al_register_event_source(ctx->queue, al_get_timer_event_source(ctx->timer));
    ctx->done = false;
    ctx->redraw = true;
    printf("Init success\n");
    return 0;
}

int loop_gui(GUI_CONTEXT *ctx)
{
    /**
     */
    al_start_timer(ctx->timer);
    /**
      */


    printf("Before Thread\n"); 
    struct ALIEN alien1;
    alien1.ctx = ctx;
    alien1.image = al_load_bitmap("assets/alfa25.png");
    alien1.x = 35;
    alien1.y = 400;
    

    pthread_t thread_id; 
    pthread_create(&thread_id, NULL, moveAlien, (void*)&alien1);

  	timer = al_create_timer(1.0 / 60);
   	al_start_timer(timer);

            
    while (1)
    {
        /**
         */
        al_wait_for_event(ctx->queue, &(ctx->event));
        /**
         */
        switch (ctx->event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            /**
             * Logic here 
             */
            ctx->redraw = true;
            break;
        /**
         */
        case ALLEGRO_EVENT_KEY_DOWN:
        /**
         */
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            ctx->done = true;
            break;
        }
        /**
         */
        if (ctx->done)
        {
            printf("Done\n");
            break;
        }
        /**
         */
        if (ctx->redraw && al_is_event_queue_empty(ctx->queue))
        {

            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(ctx->background, 0, 0, 1);
            drawmap(ctx);
            al_draw_bitmap(ctx->alfaCommunity, 5, 470, 0);
            al_draw_bitmap(ctx->betaCommunity, 775, 20, 0);
            al_draw_bitmap(alien1.image, alien1.x, alien1.y, 0);
            al_flip_display();
            ctx->redraw = false;
        }
    }
    finalize_gui(ctx);
}

int finalize_gui(GUI_CONTEXT *ctx)
{
    al_destroy_font(ctx->font);
    al_destroy_display(ctx->disp);
    al_destroy_timer(ctx->timer);
    al_destroy_event_queue(ctx->queue);
    al_destroy_bitmap(ctx->background);
    al_destroy_bitmap(ctx->path);
}

int set_background(GUI_CONTEXT *ctx)
{
    must_init(al_init_image_addon(), "image addon");
    ctx->background = al_load_bitmap("assets/background.png");
    ctx->path = al_load_bitmap("assets/path.png");
    ctx->bridge = al_load_bitmap("assets/bridge.png");
    ctx->alfaCommunity = al_load_bitmap("assets/alfaplanet.png");
    ctx->betaCommunity = al_load_bitmap("assets/betaplanet.png");
    must_init(ctx->background, "background");
    must_init(ctx->path, "path");
    return 0;
}
// 

void *moveAlien(void *args)
{
    sleep(2);
    struct ALIEN *myAlien = (ALIEN*) args;
    while (myAlien->y>10)
    {
        // al_wait_for_event(myAlien->ctx->queue, &(myAlien->ctx->event));
        usleep(100);
        myAlien->y-=0.01;
    }
}

int add_character(GUI_CONTEXT *ctx, int id, int type, int dx, int dy){
    
}

int * create_map(int lenA){
    map = malloc(3*sizeof(PATH*));
    map[0] = alfaexit;
    map[1] = alfaentrance;
    map[2] = northavenue;

}

void drawmap(GUI_CONTEXT *ctx)//, int lenA, int lenB, int lenC)
{
    // Alfa Community Entrance
    int posxInit = 70;
    int posyInit = 500;
    for(int i=0;i<ENTRANCE_COUNT;i++){
        alfaentrance[i].x = posxInit;
        alfaentrance[i].y = posyInit-40*i;
        alfaentrance[i].height = 40;
        alfaentrance[i].width = 40;
        alfaentrance[i].image = ctx->path;
        alfaentrance[i].blocked = 0;
        al_draw_bitmap(alfaentrance[i].image, alfaentrance[i].x, alfaentrance[i].y, 0);
    }

    // Alfa Community Exit
    posxInit = 150;
    posyInit = 500;
    for(int i=0;i<EXIT_COUNT;i++){
        alfaexit[i].x = posxInit;
        alfaexit[i].y = posyInit-40*i;
        alfaexit[i].height = 40;
        alfaexit[i].width = 40;
        alfaexit[i].image = ctx->path;
        alfaexit[i].blocked = 0;
        al_draw_bitmap(alfaexit[i].image, alfaexit[i].x, alfaexit[i].y, 0);
    }
    posxInit = 150;
    posyInit = 20;
    int k = 0;
    // North Avenue
    for(int i=0;i<AVENUE_COUNT;i++){
        if(i==15){
            posxInit = 150;
            posyInit = 60;
            k=0;
        }
        northavenue[i].x = posxInit+40*k;
        northavenue[i].y = posyInit;
        northavenue[i].height = 40;
        northavenue[i].width = 40;
        northavenue[i].image = ctx->path;
        northavenue[i].blocked = 0;
        // al_draw_bitmap(northavenue[i].image, , northavenue[i].y, 0);
        al_draw_rotated_bitmap(northavenue[i].image,0,0,northavenue[i].x,northavenue[i].y, ALLEGRO_PI/2, 0);
        k++;
    }
    // #########################################
    // Beta Community Exit
    posxInit = 810;
    posyInit = 120;
    for(int i=0;i<EXIT_COUNT;i++){
        betaexit[i].x = posxInit;
        betaexit[i].y = posyInit+40*i;
        betaexit[i].height = 40;
        betaexit[i].width = 40;
        betaexit[i].image = ctx->path;
        betaexit[i].blocked = 0;
        al_draw_bitmap(betaexit[i].image, betaexit[i].x, betaexit[i].y, 0);
    }

    // Beta Community Entrance
    posxInit = 890;
    posyInit = 120;
    for(int i=0;i<ENTRANCE_COUNT;i++){
        betaentrance[i].x = posxInit;
        betaentrance[i].y = posyInit+40*i;
        betaentrance[i].height = 40;
        betaentrance[i].width = 40;
        betaentrance[i].image = ctx->path;
        betaentrance[i].blocked = 0;
        al_draw_bitmap(betaentrance[i].image, betaentrance[i].x, betaentrance[i].y, 0);
    }

    posxInit = 850;
    posyInit = 560;
    k = 0;
    // South Avenue
    for(int i=0;i<AVENUE_COUNT;i++){
        if(i==15){
            posxInit = 850;
            posyInit = 600;
            k=0;
        }
        southavenue[i].x = posxInit-40*k;
        southavenue[i].y = posyInit;
        southavenue[i].height = 40;
        southavenue[i].width = 40;
        southavenue[i].image = ctx->path;
        southavenue[i].blocked = 0;
        al_draw_bitmap(southavenue[i].image, southavenue[i].x, southavenue[i].y, 0);
        k++;
    }
}
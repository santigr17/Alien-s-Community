#ifndef CEGUI_HEADER_FILE
#define CEGUI_HEADER_FILE
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
/**
 * This is the basic structure to render a gui
 */
typedef struct
{
    /**
     * We need a timer and an event queue to 
     * ensure the game runs at a consistent speed; 
     */ 
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    /**
     * Pointer to the Alegro display
     */ 
    ALLEGRO_DISPLAY *disp;
    /**
     * Allegro font pointer
     */ 
    ALLEGRO_FONT *font;
    /**
     * Controls when to finisthe game
     */ 
    bool done;
    /**
     *  Controls when to repaint the window
     */
    bool redraw;
    /**
     * Abstraction of General/GUI envent
     */ 
    ALLEGRO_EVENT event;

    /**
     * Background representation
     */
    ALLEGRO_BITMAP *background;
} GUI_CONTEXT;
/**
 * Movement Bouncer
 */ 
typedef struct CHARACTER
{
    /**
     * 
     */
    int id;
    /**
     * Coordinates
     */
    float x, y;
    /**
     * The way we set a velocity
     */
    float dx, dy;
    /**
     * type 
     */ 
} CHARACTER;
int init_gui(GUI_CONTEXT *ctx);
int loop_gui(GUI_CONTEXT *ctx);
int finalize_gui(GUI_CONTEXT *ctx);
int set_background(GUI_CONTEXT *ctx);

int add_character(GUI_CONTEXT *ctx, int id, int type, int dx, int dy);
#endif

//
// Created by OfferleA on 6/11/2024.
//

#ifndef ARKANOID_DROID_H
#define ARKANOID_DROID_H


#include <SDL_rect.h>
#include <time.h>
#include "brick.h"

#define DROID_BLUE_MAX_FRAME 8
#define DROID_ATOM_MAX_FRAME 24
#define DROID_GREEN_MAX_FRAME 11
#define DROID_DEATH_MAX_FRAME 6

extern SDL_Rect srcDroidBlue[DROID_BLUE_MAX_FRAME];
extern SDL_Rect srcDroidAtom[DROID_ATOM_MAX_FRAME];
extern SDL_Rect srcDroidGreen[DROID_GREEN_MAX_FRAME];
extern SDL_Rect srcDroidDeath[DROID_DEATH_MAX_FRAME];


typedef struct {
    int x, y;
    int w, h;
    int vx, vy;
    int type;
    SDL_Rect srcRect;
    int active;
    int frame_nu;
    int health;
} droid;

void create_droid(droid *d, int x, int y);
void update_droid(droid *d);
void update_droids(droid *droids, int droid_count, brick *bricks, int brick_count);
void move_droid(droid *d, brick *bricks, int brick_count);
void damage_droid(droid *d);

#endif //ARKANOID_DROID_H

//
// Created by OfferleA on 5/28/2024.
//

#ifndef ARKANOID_BRICK_H
#define ARKANOID_BRICK_H

#include "powerup.h"
#include <SDL2/SDL.h>

typedef struct {
    int x, y;
    int w, h;
    SDL_Rect srcRect;
    int health;
    PowerUp powerup;
} brick;

void create_brick(brick *brick, int x, int y, int w, int h, int health);
void damage_brick(brick *b);
int is_brick_dead(brick *b);
int is_brick_breakable(brick *b);

#endif //ARKANOID_BRICK_H

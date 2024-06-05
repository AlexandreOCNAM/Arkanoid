//
// Created by OfferleA on 5/28/2024.
//

#ifndef ARKANOID_BRICK_H
#define ARKANOID_BRICK_H

#include "powerup.h"
#include <SDL2/SDL.h>
#include "constant.h"
#include <stdbool.h>

typedef struct {
    int x, y;
    int w, h;
    SDL_Rect srcRect;
    int health;
    PowerUp powerup;
    bool silver;
    bool gold;
    int points;
} brick;

void create_brick(brick *brick, int x, int y, int w, int h, int health, int points);
void damage_brick(brick *b);
void animateBricks(double delta_t);
SDL_Rect getBrickSrcRect(brick *b);

#endif //ARKANOID_BRICK_H

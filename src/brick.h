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
    int isSilver;
    int isGold;
    int points;
} brick;

static SDL_Rect goldenBrickStates[6] = {
        {0, 48, 32, 16},
        {32, 48, 32, 16},
        {64, 48, 32, 16},
        {96, 48, 32, 16},
        {128, 48, 32, 16},
        {160, 48, 32, 16}
};

static SDL_Rect silverBrickStates[6] = {
        {0, 32, 32, 16},
        {32, 32, 32, 16},
        {64, 32, 32, 16},
        {96, 32, 32, 16},
        {128, 32, 32, 16},
        {160, 32, 32, 16}
};
void create_brick(brick *brick, int x, int y, int w, int h, int health, int points);
int damage_brick(brick *b);
int is_brick_dead(brick *b);
int is_brick_breakable(brick *b);
void update_bricks(double delta_t);
SDL_Rect get_brick_rect(brick *b);

#endif //ARKANOID_BRICK_H

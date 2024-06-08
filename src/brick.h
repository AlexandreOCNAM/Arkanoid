//
// Created by OfferleA on 5/28/2024.
//

#ifndef ARKANOID_BRICK_H
#define ARKANOID_BRICK_H

#include "powerup.h"
#include <SDL2/SDL.h>
#include "spriteConstant.h"
extern int powerup_count;

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

void create_brick(brick *brick, int x, int y, int w, int h, int health, int points);
int damage_brick(brick *b);
int is_brick_dead(brick *b);
int is_brick_breakable(brick *b);
void update_bricks(double delta_t);
SDL_Rect get_brick_rect(brick *b);
PowerUpType assign_random_powerup();

#endif //ARKANOID_BRICK_H

//
// Created by OfferleA on 5/29/2024.
//

#ifndef ARKANOID_POWERUP_H
#define ARKANOID_POWERUP_H
#include <SDL2/SDL.h>
#include "paddle.h"
#include "constant.h"
#include "spriteConstant.h"

typedef enum {
    NONE,
    SLOW,
    CATCH,
    EXPAND,
    DIVIDE,
    LASER,
    BREAK,
    PLAYER
} PowerUpType;

typedef struct {
    int x, y;
    int w, h;
    PowerUpType type;
    SDL_Rect srcRect;
    int active;
    int current_state;
} PowerUp;

PowerUp create_powerup(int x, int y, PowerUpType type);
void update_powerups(PowerUp powerups[], int *powerup_count, paddle *p, double delta_t);
void update_powerup_animation(PowerUp *pu, double delta_t);

#endif //ARKANOID_POWERUP_H
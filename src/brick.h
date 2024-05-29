//
// Created by OfferleA on 5/28/2024.
//

#ifndef ARKANOID_BRICK_H
#define ARKANOID_BRICK_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;
    SDL_Rect srcRect;
    int health;
}Brick;

void create_brick(Brick *brick, int x, int y, int w, int h, int health);
void damage_brick(Brick *b);

#endif //ARKANOID_BRICK_H

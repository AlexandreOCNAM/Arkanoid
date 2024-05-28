#ifndef BRICK_H
#define BRICK_H

#include "position.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    Position pos;
    int width;
    int height;
    bool destroyed;
    SDL_Rect srcRect;
} Brick;

void brick_draw(Brick *brick, SDL_Renderer *renderer);
void brick_init(Brick *brick, int x, int y, int width, int height);

#endif //BRICK_H

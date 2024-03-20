//
// Created by alexa on 3/19/2024.
//

#ifndef BRICK_H
#define BRICK_H
#include <SDL_rect.h>
#include <SDL_surface.h>

#include "position.h"
#include "stdint.h"


typedef struct
{
    int x, y;
    int w = 32, h = 16;
    uint8_t health;
} brick;


void draw_brick(SDL_Surface *win_surf, brick *b);




#endif //BRICK_H

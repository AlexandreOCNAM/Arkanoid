//
// Created by OfferleA on 5/28/2024.
//

#ifndef ARKANOID_GRAPHICS_H
#define ARKANOID_GRAPHICS_H

#include <SDL2/SDL.h>
#include "ball.h"
#include "paddle.h"
#include "brick.h"



SDL_Surface *load_image(const char *path);

SDL_Surface* init_window();
void blit_background(SDL_Rect *dest);
void draw_ball(ball *b);
void draw_paddle(paddle *p);
void draw_brick(brick *b);
void draw_bricks(brick *b, int n);
void draw_powerup(PowerUp *p);
void draw_powerups(PowerUp *p, int n);
void update_window();

#endif //ARKANOID_GRAPHICS_H

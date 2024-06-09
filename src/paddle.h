//
// Created by OfferleA on 5/28/2024.
//

#ifndef ARKANOID_PADDLE_H
#define ARKANOID_PADDLE_H
#include <SDL2/SDL.h>
#include "constant.h"
#include "spriteConstant.h"


typedef struct {
    int x, y;
    int w, h;
    int vx, vy;
    SDL_Rect srcRect;
} paddle;

paddle create_paddle(int paddle_width);
void strafe_paddle(paddle *p, int direction);
void invert_paddle_velocity(paddle *p);
void move_paddle(paddle *p);
void extend_paddle(paddle *p);
void reset_paddle(paddle *p, int paddle_width);
#endif //ARKANOID_PADDLE_H

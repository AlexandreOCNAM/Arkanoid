#ifndef __BALL_H__
#define __BALL_H__

#include <SDL_rect.h>
#include "brick.h"
#include "paddle.h"

typedef struct {
    int x, y;
    int w, h;
    int vx;
    int vy;
    SDL_Rect* rect;
} ball;

ball create_ball();
void move_ball(ball *b, SDL_Rect *screen, paddle *p, brick *bricks, int n);


#endif
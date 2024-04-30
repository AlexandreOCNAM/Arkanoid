#ifndef BALL_H_
#define BALL_H_

#include "includes.h"

typedef struct {
    double x, y;
} speed;

typedef struct
{
    SDL_Rect rect;
    speed v;
} ball;

ball create_ball();

void invert_x_speed(ball *b);
void invert_y_speed(ball *b);

void move_ball(ball *b);

void ball_collide_walls(ball *b, SDL_Rect *rect);
void ball_collide_rect(ball *b, SDL_Rect *r1);
void ball_collide_paddle(ball *b, SDL_Rect *r1);

#endif
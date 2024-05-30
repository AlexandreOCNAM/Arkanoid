#ifndef __BALL_H__
#define __BALL_H__

#include <SDL2/SDL_rect.h>
#include "brick.h"
#include "paddle.h"

#define BALL_MAX_SPEED 7

typedef struct {
    int x, y;
    int w, h;
    int vx;
    int vy;
    SDL_Rect* rect;
} ball;

ball create_ball();
void move_ball(ball *b, paddle *p, brick *bricks, int n);
void apply_ball_powerup(ball *b, PowerUp *p);
int is_colliding(ball *b, SDL_Rect *r);
void handle_paddle_collision(ball *b, paddle *p);
void handle_brick_collision(ball *b, brick *br);
void reset_ball(ball *b);
void launch_ball(ball *b);


#endif
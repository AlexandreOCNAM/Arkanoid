#ifndef __BALL_H__
#define __BALL_H__

#include <SDL2/SDL_rect.h>
#include "brick.h"
#include "paddle.h"
#include "constant.h"
#include "level.h"

#define BALL_MAX_SPEED 7

typedef struct {
    int x, y;
    int w, h;
    int vx;
    int vy;
    SDL_Rect* rect;
    int active;
} ball;

ball create_ball();
void move_balls(ball *balls, int balls_count, paddle *p, brick *bricks, int n, level *l);
int move_ball(ball *b, paddle *p, brick *bricks, int n, level *l);
void apply_ball_powerup(ball *b, PowerUp *p);
int is_colliding(ball *b, SDL_Rect *r);
void handle_paddle_collision(ball *b, paddle *p);
void handle_brick_collision(ball *b, brick *br);
void reset_balls(ball *balls, int ball_count);
void launch_ball(ball *b);
void slow_ball(ball *b);
void split_ball(ball balls[], int *ball_count);

#endif
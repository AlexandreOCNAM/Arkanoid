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
    int is_catch;
} ball;

void create_ball(ball *b);
int move_balls(ball **balls, int *balls_count, paddle *p, brick *bricks, int n, level *l);
void move_ball(ball *b, paddle *p, brick *bricks, int n);
void set_ball_speed(ball *b, int vx, int vy);
void apply_ball_powerup(ball *b, PowerUp *p);
int is_colliding(ball *b, SDL_Rect *r);
void handle_paddle_collision(ball *b, paddle *p);
void handle_brick_collision(ball *b, brick *br);
void reset_balls(ball **balls, int *ball_count);
void launch_ball(ball *b);
void split_balls(ball **balls, int *ball_count);

#endif
#ifndef BALL_H_
#define BALL_H_

#include <SDL_rect.h>
#include <SDL_surface.h>
#include <stdbool.h>
#include "position.h"


typedef struct {
    double x, y;
} speed;

typedef struct
{
    double x, y;
    speed v;
} ball;

void invert_x_speed(ball *b);
void invert_y_speed(ball *b);

void move_ball(ball *b);
bool is_point_inside_rect(Point p, SDL_Rect *r);
void ball_collide_walls(ball *b, SDL_Rect *rect);
void ball_collide_rect(ball *b, SDL_Rect *r1);

#endif
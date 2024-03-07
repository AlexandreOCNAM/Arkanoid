#ifndef BALL_H_
#define BALL_H_

#include <SDL_rect.h>
#include <SDL_surface.h>

typedef enum {
  HORZ,
  VERT,
  NONE,
  BOTH
} collision_type;

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

void draw_ball(SDL_Surface *win_surf, SDL_Surface *plancheSprites, SDL_Rect srcBall, ball _ball);
collision_type ball_collide_wall(ball *b, int w, int h);
void ball_collide_rect(ball *b, SDL_Rect *r1);

#endif
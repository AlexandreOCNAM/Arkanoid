//
// Created by alexa on 3/7/2024.
//

#include <SDL_version.h>
#include "../includes/ball.h"


void invert_x_speed(ball *b){
    b->v.x *= -1;
}

void invert_y_speed(ball *b){
    b->v.y *= -1;
}

void move_ball(ball *b){
    b->x += b->v.x;
    b->y += b->v.y;
}

void draw_ball(SDL_Surface *win_surf, SDL_Surface *plancheSprites, SDL_Rect srcBall, ball _ball){
    SDL_Rect dstBall = {_ball.x, _ball.y, 0, 0};
    SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);
}


collision_type ball_collide_wall(ball *b, int w, int h){
  if (b->x < 0 || b->x > w - 25){
    return HORZ;
  }
  else if (b->y < 0 || b->y > h - 25){
    return VERT;
  }
  return NONE;
}


collision_type ball_collide_rect(ball *b, SDL_Rect *r1){
  // print sdl version
  SDL_version compiled;
  SDL_Rect r2 = {b->x, b->y, 25, 25};
  SDL_Rect res = {0, 0, 0, 0};
  // if the ball collides horizontally, return HORZ
  if (SDL_IntersectRect(&r2, r1, &res))
  {
    if (res.w > res.h)
    {
      return HORZ;
    }
    else if (res.w < res.h)
    {
      return VERT;
    }
  }

  // if the ball doesn't collide, return NONE
  return NONE;
}

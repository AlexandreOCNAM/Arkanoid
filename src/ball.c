//
// Created by alexa on 3/7/2024.
//

#include <SDL_version.h>
#include "../includes/ball.h"
#include <stdbool.h>


bool checkLineIntersection(Point p1, Point p2, Point left, Point right);

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

void ball_collide_walls(ball *b, SDL_Rect *rect){
  if (b->x < rect->x || b->x > rect->w - 25){
    invert_x_speed(b);
  }
  else if (b->y < rect->y || b->y > rect->h - 25){
    invert_y_speed(b);
  }
}


float max(float a, float b){
  if (a > b){
    return a;
  }
  return b;
}





void ball_collide_rect(ball *b, SDL_Rect *r1){
  ball next = *b;
  move_ball(&next);

  for (int i = 0; i < 8; i++){
    Point p = {b->x + 24 + (i % 2 == 0 ? 12 : 2.5), b->y + 24 + (i < 4 ? -12 : -2.5)};
    Point p2 = {next.x + 24 + (i % 2 == 0 ? 12 : 2.5), next.y + 24 + (i < 4 ? -12 : -2.5)};

    if ((p.x >= r1->x && p.x <= r1->x + r1->w && p.y >= r1->y && p.y <= r1->y + r1->h) ||
        (p2.x >= r1->x && p2.x <= r1->x + r1->w && p2.y >= r1->y && p2.y <= r1->y + r1->h)) {
      if (i % 2 == 0){
        invert_y_speed(b);
      } else {
        invert_x_speed(b);
      }
      return;
    }
  }


//  SDL_Rect r2 = {b->x, b->y, 24, 24};
//  SDL_Rect res = {0, 0, 0, 0};
//  // if the ball collides horizontally, return HORZ
//  if (SDL_IntersectRect(&r2, r1, &res))
//  {
//    if (res.w > res.h)
//    {
//      invert_x_speed(b);
//    }
//    else if (res.w < res.h)
//    {
//      invert_y_speed(b);
//    }
//    else {
//      invert_x_speed(b);
//      invert_y_speed(b);
//    }
//  }
//  else {
//    // create a rectangle from the ball to next position
//    SDL_Rect r3 = {b->x + b->v.x, b->y + b->v.y, 24, 24};
//    if (SDL_IntersectRect(&r3, r1, &res)) {
//      if (res.w > res.h) { // ball collides horizontally
//        invert_y_speed(b);
//      } else if (res.w < res.h) { // ball collides vertically
//        invert_y_speed(b);
//      }
//    }
//
//  }

}

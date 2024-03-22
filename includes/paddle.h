//
// Created by alexa on 3/8/2024.
//

#ifndef ARKANOID_PADDLE_H
#define ARKANOID_PADDLE_H


#include "position.h"
#include "ball.h"

typedef struct {
  SDL_Rect rect;
  speed v;
} paddle;

paddle create_paddle();


void invert_speed(paddle* p);
void move_paddle(paddle *p);
void strafe_left(paddle *p);
void strafe_right(paddle *p);
void paddle_collide_walls(paddle *p, int width);

inline int ball_inside_paddle(SDL_Rect *p, ball *b)
{
  return (b->rect.x >= p->x && b->rect.x <= p->x + p->w && b->rect.y >= p->y && b->rect.y <= p->y + p->h);
}

inline void paddle_collide_ball(SDL_Rect *p, ball *b) {
  ball next = *b;
  move_ball(&next);

  position check_pos[8] = {
      {p->x + 12, p->y},
      {p->x + 24, p->y + 12},
      {p->x + 12, p->y + 24},
      {p->x, p->y + 12},
      {p->x + 24 - 2.5, p->y + 2.5},
      {p->x + 24 -2.5, p->y + 24 - 2.5},
      {p->x + 2.5, p->y + 24 - 2.5},
      {p->x + 2.5, p->y + 2.5}
  };

  for (int i = 0; i < 8; i++){
    Point p1 = {check_pos[i].x, check_pos[i].y};
    Point p2 = {next.rect.x + 24, next.rect.y + 24};

    if ((p1.x >= p->x && p1.x <= p->x + p->w && p1.y >= p->y && p1.y <= p->y + p->h) ||
        (p2.x >= p->x && p2.x <= p->x + p->w && p2.y >= p->y && p2.y <= p->y + p->h)) {
       // create a SDL_Rect for the ball then check if it collides with the paddle
      SDL_Rect r2 = {b->rect.x, b->rect.y, 24, 24};
      SDL_Rect res = {0, 0, 0, 0};
      // if the ball collides horizontally invert the y speed
      if (SDL_IntersectRect(&r2, p, &res))
      {
        if (res.w > res.h)
        {
          invert_y_speed(b);
        }
        else if (res.w < res.h)
        {
          invert_x_speed(b);
        }
        else {
          invert_x_speed(b);
          invert_y_speed(b);
        }

        // if the ball is inside the paddle, teleport it to the top of the paddle
        if (ball_inside_paddle(p, b))
        {
          b->rect.y = p->y - 25;
        }

      }
      return;
    }
  }

//  for (int i = 0; i < 8; i++){
//    Point p1 = {b->x + 24 + (i % 2 == 0 ? 12 : 2.5), b->y + 24 + (i < 4 ? -12 : -2.5)};
//    Point p2 = {next.x + 24 + (i % 2 == 0 ? 12 : 2.5), next.y + 24 + (i < 4 ? -12 : -2.5)};
//
//    if ((p1.x >= p->x && p1.x <= p->x + p->w && p1.y >= p->y && p1.y <= p->y + p->h) ||
//        (p2.x >= p->x && p2.x <= p->x + p->w && p2.y >= p->y && p2.y <= p->y + p->h)) {
//      if (i % 2 == 0){
//        invert_y_speed(b);
//      } else {
//        invert_x_speed(b);
//      }
//      return;
//    }
//  }
}


#endif //ARKANOID_PADDLE_H

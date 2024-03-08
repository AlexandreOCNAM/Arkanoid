//
// Created by alexa on 3/8/2024.
//

#ifndef ARKANOID_PADDLE_H
#define ARKANOID_PADDLE_H


#include "position.h"
#include "ball.h"

typedef struct {
  position pos;
  double w, h;
  speed v;
} paddle;


void move_paddle(paddle *p);

void paddle_collide_walls(paddle *p, int w, int h);
void paddle_collide_ball(SDL_Rect *p, ball *b);

void paddle_collide_ball(SDL_Rect *p, ball *b) {
  ball next = *b;
  move_ball(&next);

  for (int i = 0; i < 8; i++){
    Point p1 = {b->x + 24 + (i % 2 == 0 ? 12 : 2.5), b->y + 24 + (i < 4 ? -12 : -2.5)};
    Point p2 = {next.x + 24 + (i % 2 == 0 ? 12 : 2.5), next.y + 24 + (i < 4 ? -12 : -2.5)};

    if ((p1.x >= p->x && p1.x <= p->x + p->w && p1.y >= p->y && p1.y <= p->y + p->h) ||
        (p2.x >= p->x && p2.x <= p->x + p->w && p2.y >= p->y && p2.y <= p->y + p->h)) {
      if (i % 2 == 0){
        invert_y_speed(b);
      } else {
        invert_x_speed(b);
      }
      return;
    }
  }
}


#endif //ARKANOID_PADDLE_H

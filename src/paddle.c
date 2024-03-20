//
// Created by OfferleA on 3/20/2024.
//

#include "../includes/paddle.h"

paddle create_paddle()
{
  const paddle p = {
    {128, 600-16, 128, 32},
    {10, 0}
  };
  return p;
}

void invert_speed(paddle* p)
{
  p->v.x = -p->v.x;
}

void move_paddle(paddle *p)
{
  p->rect.x += p->v.x;
}

void strafe_left(paddle* p)
{
  p->rect.x -= p->v.x;
}

void strafe_right(paddle* p)
{
  p->rect.x += p->v.x;
}

void paddle_collide_walls(paddle *p, const int width)
{
  if (p->rect.x <= 0 || p->rect.x > width - p->rect.w)
  {
    if (p->rect.x <= 0)
    {
      p->rect.x = 0;
    }
    else
    {
      p->rect.x = width - p->rect.w;
    }
  }
}

//
// Created by OfferleA on 5/28/2024.
//

#ifndef ARKANOID_COLLISIONS_H
#define ARKANOID_COLLISIONS_H

#include "ball.h"
#include "paddle.h"
#include "brick.h"

void ball_paddle_collision(ball *b, paddle *p);
void ball_brick_collision(ball *b, brick *bricks, int n);
void ball_wall_collision(ball *b);

void paddle_wall_collision(paddle *p);

#endif //ARKANOID_COLLISIONS_H

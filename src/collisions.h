//
// Created by OfferleA on 5/28/2024.
//

#ifndef ARKANOID_COLLISIONS_H
#define ARKANOID_COLLISIONS_H

#include "ball.h"
#include "paddle.h"
#include "brick.h"

// Pré-déclaration de la structure PowerUp si nécessaire
struct PowerUp;

void ball_powerup_collision(ball *b, PowerUp *p);
void paddle_powerup_collision(paddle *p, PowerUp *pu);

#endif //ARKANOID_COLLISIONS_H

//
// Created by OfferleA on 5/28/2024.
//

#ifndef ARKANOID_BRICK_H
#define ARKANOID_BRICK_H

#include "powerup.h"

typedef struct {
    int x, y;
    int w, h;
    int health;
    PowerUp powerup;
} brick;

brick create_brick(int x, int y, int w, int h, int health);
void damage_brick(brick *b);

#endif //ARKANOID_BRICK_H

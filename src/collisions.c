//
// Created by OfferleA on 5/28/2024.
//

#include <stdio.h>
#include "collisions.h"

void ball_powerup_collision(ball *b, PowerUp *p) {
    if (b->x + b->w >= p->x && b->x <= p->x + p->w && b->y + b->h >= p->y && b->y <= p->y + p->h) {
        p->active = 0;
        apply_ball_powerup(b, p);
    }
}

void paddle_powerup_collision(paddle *p, PowerUp *pu) {
    if (p->x + p->w >= pu->x && p->x <= pu->x + pu->w && p->y + p->h >= pu->y && p->y <= pu->y + pu->h) {
        pu->active = 0;
        apply_powerup(p, pu->type);
    }
}
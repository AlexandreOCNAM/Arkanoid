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
    if (b->y < 0 || b->y > 600 - b->h) {
        b->vy = -b->vy;
    }
//    move_ball(b);
}

void ball_brick_collision(ball *b, brick *bricks, int n) {
    for (int i = 0; i < n; i++) {
        if (bricks[i].health > 0) {
            if (b->x < bricks[i].x + bricks[i].w &&
                b->x + b->w > bricks[i].x &&
                b->y < bricks[i].y + bricks[i].h &&
                b->y + b->h > bricks[i].y) {
                damage_brick(&bricks[i]);
//                move_ball(b);
            }
        }
    }

}

void ball_paddle_collision(ball *b, paddle *p) {
    // if the paddle is moving towards the ball and the ball is moving towards the paddle
    if ((p->vx > 0 && b->vx > 0) || (p->vx < 0 && b->vx < 0)) {
        if (b->x < p->x + p->w &&
            b->x + b->w > p->x &&
            b->y < p->y + p->h &&
            b->y + b->h > p->y) {
//            move_ball(b);
        }
    } else {
        if (b->x < p->x + p->w &&
            b->x + b->w > p->x &&
            b->y < p->y + p->h &&
            b->y + b->h > p->y) {
//            move_ball(b);
        }
    }
}

void paddle_powerup_collision(paddle *p, PowerUp *pu) {
    if (p->x + p->w >= pu->x && p->x <= pu->x + pu->w && p->y + p->h >= pu->y && p->y <= pu->y + pu->h) {
        pu->active = 0;
        apply_powerup(p, pu->type);
    }
    else if (p->x > 600 - p->w) {
        p->x = 600 - p->w;
    }
}
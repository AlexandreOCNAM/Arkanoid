//
// Created by OfferleA on 5/28/2024.
//

#include <stdio.h>
#include "collisions.h"

void ball_wall_collision(ball *b) {
    if (b->x < 0 || b->x > 600 - b->w) {
        b->vx = -b->vx;
    }
    if (b->y < 0 || b->y > 600 - b->h) {
        b->vy = -b->vy;
    }
//    move_ball(b);
}

void ball_brick_collision(ball *b, Brick *bricks, int n) {
    for (int i = 0; i < n; i++) {
        if (bricks[i].health > 0) {
            if (b->x < bricks[i].x + bricks[i].width &&
                b->x + b->w > bricks[i].x &&
                b->y < bricks[i].y + bricks[i].height &&
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
    }
    else {
        if (b->x < p->x + p->w &&
            b->x + b->w > p->x &&
            b->y < p->y + p->h &&
            b->y + b->h > p->y) {
//            move_ball(b);
        }
    }

}

void paddle_wall_collision(paddle *p) {
    if (p->x < 0 ) {
           p->x = 0;
    }
    else if (p->x > 600 - p->w) {
        p->x = 600 - p->w;
    }
}



//
// Created by OfferleA on 5/28/2024.
//

#include "paddle.h"
#include "constant.h"

paddle create_paddle(int paddle_width) {
    paddle result = {
            (PLAYABLE_ZONE_WIDTH-paddle_width)/2, PLAYABLE_ZONE_HEIGHT -32, paddle_width, 16, 7, 0
    };
    return result;
}

void move_paddle(paddle *p) {
    p->x += p->vx;
}

void invert_paddle_velocity(paddle *p) {
    p->vx = -p->vx;
}

void strafe_paddle(paddle *p, int direction) {
    if (direction == 0) {
        p->vx = -5;
    }
    else if (direction == 1) {
        p->vx = 5;
    }
    else {
        p->vx = 0;
    }
    if (p->x < PLAYABLE_ZONE_WIDTH_START) {
        p->x = PLAYABLE_ZONE_WIDTH_START;
    }
    if (p->x + p->w > PLAYABLE_ZONE_WIDTH) {
        p->x = PLAYABLE_ZONE_WIDTH - p->w;
    }
    p->x += p->vx;
}

void apply_powerup(paddle *p, int type) {
    if (type == 0) {
        p->w = 128;
    }
    else if (type == 1) {
        p->w = 64;
    }
    else if (type == 2) {
        p->w = 256;
    }
}

void reset_paddle(paddle *p, int paddle_width) {
    p->x = PLAYABLE_ZONE_WIDTH-paddle_width)/2;
    p->y = PLAYABLE_ZONE_HEIGHT - 32;
    p->w = paddle_width;
    p->h = 16;
    p->vx = 7;
    p->vy = 0;
}

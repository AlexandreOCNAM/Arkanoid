//
// Created by OfferleA on 5/28/2024.
//

#include "paddle.h"

paddle create_paddle() {
    paddle result = {
            128, 600-16, 128, 32, 5, 0
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

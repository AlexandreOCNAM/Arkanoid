//
// Created by OfferleA on 3/20/2024.
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


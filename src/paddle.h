//
// Created by OfferleA on 5/28/2024.
//

#ifndef ARKANOID_PADDLE_H
#define ARKANOID_PADDLE_H

typedef struct {
    int x, y;
    int w, h;
    int vx, vy;
} paddle;

paddle create_paddle(int paddle_width);
void strafe_paddle(paddle *p, int direction);
void invert_paddle_velocity(paddle *p);
void move_paddle(paddle *p);
void apply_powerup(paddle *p, int type);
void reset_paddle(paddle *p);
#endif //ARKANOID_PADDLE_H

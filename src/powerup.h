//
// Created by OfferleA on 5/29/2024.
//

#ifndef ARKANOID_POWERUP_H
#define ARKANOID_POWERUP_H


typedef struct {
    int x, y;
    int w, h;
    int type;
    int active;
} PowerUp;

PowerUp create_powerup(int x, int y);

#endif //ARKANOID_POWERUP_H

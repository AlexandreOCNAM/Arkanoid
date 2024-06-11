//
// Created by OfferleA on 6/11/2024.
//

#ifndef ARKANOID_LASER_H
#define ARKANOID_LASER_H

#include "ball.h"

#define MAX_LASERS 10  // Maximum number of lasers

typedef struct {
    int x, y;
    int w, h;
    int vy;
    SDL_Rect srcRect;
    int active;
} laser;

void create_laser(laser *l, int x, int y);
void update_lasers(laser *lasers,const int *laser_count, brick *bricks, const int *n);
int active_lasers(laser *lasers, const int *laser_count);

#endif //ARKANOID_LASER_H

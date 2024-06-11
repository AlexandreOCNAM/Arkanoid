//
// Created by OfferleA on 6/11/2024.
//

#include "laser.h"

#define LASER_WIDTH 4
#define LASER_HEIGHT 8
#define LASER_SPEED 8

void create_laser(laser *l, int x, int y) {
    l->x = x;
    l->y = y;
    l->w = LASER_WIDTH;
    l->h = LASER_HEIGHT;
    l->vy = -LASER_SPEED;
    l->srcRect = (SDL_Rect) {0, 0, LASER_WIDTH, LASER_HEIGHT};
    l->active = 1;
}

void update_lasers(laser lasers[],const int *laser_count, brick bricks[], const int *n) {
    for (int i = 0; i < *laser_count; i++) {
        if (lasers[i].active == 1) {
            lasers[i].y += lasers[i].vy;
            if (lasers[i].y < 0) {
                lasers[i].active = 0;
            }
            for (int j = 0; j < *n; j++) {
                if (bricks[j].health > 0) {
                    SDL_Rect laser_rect = {lasers[i].x, lasers[i].y, lasers[i].w, lasers[i].h};
                    SDL_Rect brick_rect = {bricks[j].x, bricks[j].y, bricks[j].w, bricks[j].h};
                    if (SDL_HasIntersection(&laser_rect, &brick_rect)) {
                        lasers[i].active = 0;
                        damage_brick(&bricks[j]);
                    }
                }
            }
        }
    }
}

int active_lasers(laser lasers[], const int *laser_count) {
    int count = 0;
    for (int i = 0; i < *laser_count; i++) {
        if (lasers[i].active == 1) {
            count++;
        }
    }
    return count;
}

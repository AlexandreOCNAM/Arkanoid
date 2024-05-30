//
// Created by OfferleA on 5/28/2024.
//

#include "brick.h"

void create_brick(brick *brick, int x, int y, int width, int height, int health) {
    brick->x = x;
    brick->y = y;
    brick->w = width;
    brick->h = height;
    brick->health = health;
    //printf("Created brick at (%d, %d) with health %d\n", x, y, health);
}


void damage_brick(brick *b) {
    b->health--;
}

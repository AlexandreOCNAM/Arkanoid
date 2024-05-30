//
// Created by OfferleA on 5/28/2024.
//

#include "brick.h"

void create_brick(Brick *brick, int x, int y, int width, int height, int health) {
    brick->x = x;
    brick->y = y;
    brick->width = width;
    brick->height = height;
    brick->health = health;
    //printf("Created brick at (%d, %d) with health %d\n", x, y, health);
}


void damage_brick(Brick *b) {
    b->health--;
}

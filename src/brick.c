#include "brick.h"

void create_brick(Brick *brick, int x, int y, int width, int height, int health) {
    brick->x = x;
    brick->y = y;
    brick->width = width;
    brick->height = height;
    brick->health = health;
}


void damage_brick(Brick *b) {
    b->health--;
}

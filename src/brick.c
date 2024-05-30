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
    printf("Brick at (%d, %d) damaged, health now %d\n", b->x, b->y, b->health);
    if (b->health <= 0) {
        printf("Brick at (%d, %d) destroyed\n", b->x, b->y);
    }
}

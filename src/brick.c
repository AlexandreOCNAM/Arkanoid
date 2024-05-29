#include "brick.h"

void create_brick(Brick *brick, int x, int y, int width, int height, int health) {
    brick->x = x;
    brick->y = y;
    brick->width = width;
    brick->height = height;
    brick->health = health;
    brick->destroyed = false;
}

void brick_draw(Brick *brick, SDL_Renderer *renderer) {
    if (!brick->destroyed) {
        SDL_Rect rect = {brick->x, brick->y, brick->width, brick->height};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void damage_brick(Brick *b) {
    b->health--;
}

#include "../includes/brick.h"

void brick_init(Brick *brick, int x, int y, int width, int height) {
    brick->pos.x = x;
    brick->pos.y = y;
    brick->width = width;
    brick->height = height;
    brick->destroyed = false;
}

void brick_draw(Brick *brick, SDL_Renderer *renderer) {
    if (!brick->destroyed) {
        SDL_Rect rect = {brick->pos.x, brick->pos.y, brick->width, brick->height};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}
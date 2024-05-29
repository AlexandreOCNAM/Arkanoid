#include "ball.h"
#include "collisions.h"

ball create_ball() {
    ball result = {
        .x = 0,
        .y = 96,
        .w = 24,
        .h = 24,
        .vx = 5,
        .vy = 5,
        .rect = malloc(sizeof(SDL_Rect))
    };
    result.rect->x = result.x;
    result.rect->y = result.y;
    result.rect->w = result.w;
    result.rect->h = result.h;
    return result;
}

void move_ball(ball *b, SDL_Rect *screen, paddle *p, Brick *bricks, int n) {
    if (b->x < 0 || b->x > 600 - b->w) {
        b->vx = -b->vx;
    }
    if (b->y < 0 || b->y > 600 - b->h) {
        b->vy = -b->vy;
    }

    // collision avec le paddle, si le paddle est en mouvement vers la balle, inverse la direction en X et Y de la balle
    // sinon, inverse seulement la direction en Y
    if (b->x < p->x + p->w &&
        b->x + b->w > p->x &&
        b->y < p->y + p->h &&
        b->y + b->h > p->y) {
        // Adjust the ball's y-coordinate to be just above the paddle
        b->y = p->y - b->h;
        // Invert the ball's y-velocity to make it bounce
        b->vy = -b->vy;
        // Depending on the paddle's movement, invert the x-velocity
        if ((p->vx < 0 && b->vx > 0) || (p->vx > 0 && b->vx < 0)) {
            b->vx = -b->vx;
        }
    }


    for (int i = 0; i < n; i++) {
        if (bricks[i].health > 0) {
            if (b->x < bricks[i].x + bricks[i].width &&
                b->x + b->w > bricks[i].x &&
                b->y < bricks[i].y + bricks[i].height &&
                b->y + b->h > bricks[i].y) {
                bricks[i].health--;
                b->vy = -b->vy;
            }
        }
    }

    if (b->rect->y < screen->y || b->rect->y > screen->h - b->h) {
        b->vy = -b->vy;
    }

    // collision avec les briques
    for (int i = 0; i < n; i++) {
        if (bricks[i].health > 0) {
            if (b->x < bricks[i].x + bricks[i].width &&
                b->x + b->w > bricks[i].x &&
                b->y < bricks[i].y + bricks[i].height &&
                b->y + b->h > bricks[i].y) {
                bricks[i].health--;
                b->vy = -b->vy;
            }
        }
    }

    // Déplace la balle
    b->x += b->vx;
    b->y += b->vy;

}
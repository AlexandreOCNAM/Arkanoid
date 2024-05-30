#include "ball.h"
#include "collisions.h"
#include "constant.h"

#define MAX_SPEED 7

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

void move_ball(ball *b, SDL_Rect *screen, paddle *p, brick *bricks, int n) {
    int steps = fmax(abs(b->vx), abs(b->vy));

    if (b->x < 0 || b->x > SCREEN_WIDTH - b->w) {
        b->vx = -b->vx;
    }
    if (b->y < 0 || b->y > SCREEN_HEIGHT - b->h) {
        b->vy = -b->vy;
    }

    if (b->x < p->x + p->w &&
        b->x + b->w > p->x &&
        b->y < p->y + p->h &&
        b->y + b->h > p->y) {

        float top = fabs(b->y + b->h - p->y);
        float bottom = fabs(p->y + p->h - b->y);
        float left = fabs(b->x + b->w - p->x);
        float right = fabs(p->x + p->w - b->x);

        float min = fmin(fmin(fmin(top, bottom), left), right);

        if (min == top || min == bottom) {
            b->vy = -b->vy;
        } else {
            b->vx = -b->vx;
        }
        // Adjust the direction based on the paddle's movement
        if ((p->vx < 0 && b->vx > 0) || (p->vx > 0 && b->vx < 0)) {
            b->vx = -b->vx;
        }
        b->x += b->vx;
        b->y += b->vy;
        return;
    }

    for (int step = 0; step < steps; step++) {
        int collision;
        do {
            collision = 0;
            for (int i = 0; i < n; i++) {
                if (bricks[i].health > 0) {
                    if (b->x < bricks[i].x + bricks[i].w &&
                        b->x + b->w > bricks[i].x &&
                        b->y < bricks[i].y + bricks[i].h &&
                        b->y + b->h > bricks[i].y) {
                        // Calculate the distances between the ball's edges and the brick's edges
                        float left = fabs(b->x + b->w - bricks[i].x);
                        float right = fabs(bricks[i].x + bricks[i].w - b->x);
                        float top = fabs(b->y + b->h - bricks[i].y);
                        float bottom = fabs(bricks[i].y + bricks[i].h - b->y);

                        // Find the smallest distance
                        float min = fmin(fmin(fmin(left, right), top), bottom);

                        // Invert the ball's velocity based on the smallest distance
                        if (min == left || min == right) {
                            b->vx = -b->vx;
                        } else {
                            b->vy = -b->vy;
                        }
                        damage_brick(&bricks[i]);
                        collision =1;
                        break;
                    }
                }
            }

            // Déplace la balle
            b->x += b->vx / steps;
            b->y += b->vy / steps;

        } while (collision);
    }
}

void apply_ball_powerup(ball *b, PowerUp *p) {
    switch (p->type) {
        case 0:
            b->vx = 5;
            b->vy = 5;
            break;
        case 1:
            b->vx = 10;
            b->vy = 10;
            break;
    }
}

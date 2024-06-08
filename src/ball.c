#include "ball.h"


#define MAX_SPEED 7
#define ZONE_SIZE SCREEN_HEIGHT / 4



ball create_ball() {
    ball result = {
        .x = (PLAYABLE_ZONE_WIDTH_START + PLAYABLE_ZONE_WIDTH-8)/2,
        .y = PLAYABLE_ZONE_HEIGHT - 32 - 8,
        .w = 8,
        .h = 8,
        .vx = 0,
        .vy = 0,
        .rect = malloc(sizeof(SDL_Rect))
    };
    result.rect->x = result.x;
    result.rect->y = result.y;
    result.rect->w = result.w;
    result.rect->h = result.h;
    return result;
}



void move_ball(ball *b, paddle *p, brick *bricks, int n) {
    if (b->x < PLAYABLE_ZONE_WIDTH_START || b->x > PLAYABLE_ZONE_WIDTH - b->w) {
        b->vx = -b->vx;
    }
    if (b->y < PLAYABLE_ZONE_HEIGHT_START || b->y > PLAYABLE_ZONE_HEIGHT - b->h) {
        b->vy = -b->vy;
    }
    // Check for collision with bricks
    for (int i = 0; i < n; i++) {
        if (bricks[i].health > 0 || bricks[i].health == -1) {
            if (b->x < bricks[i].x + bricks[i].w &&
                b->x + b->w > bricks[i].x &&
                b->y < bricks[i].y + bricks[i].h &&
                b->y + b->h > bricks[i].y) {

                // Handle the collision
                float top = fabs(b->y + b->h - bricks[i].y);
                float bottom = fabs(bricks[i].y + bricks[i].h - b->y);
                float left = fabs(b->x + b->w - bricks[i].x);
                float right = fabs(bricks[i].x + bricks[i].w - b->x);

                float min = fmin(fmin(fmin(top, bottom), left), right);

                if (min == top || min == bottom) {
                    b->vy = -b->vy;
                } else {
                    b->vx = -b->vx;
                }

                // Reduce the brick's health
                damage_brick(&bricks[i]);
                break;
            }
        }
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

            // Calculate the distance between the collision point and the center of the paddle
            float collisionPoint = b->x + b->w / 2;
            float paddleCenter = p->x + p->w / 2;
            float distance = collisionPoint - paddleCenter;

            // Adjust the ball's X velocity based on the distance
            float velocityFactor = distance / (p->w / 2);
            b->vx = velocityFactor * BALL_MAX_SPEED;
        } else {
            b->vx = -b->vx;
        }

        // Adjust the direction based on the paddle's movement
        if ((p->vx < 0 && b->vx > 0) || (p->vx > 0 && b->vx < 0)) {
            b->vx = -b->vx;
        }
    }
    b->x += b->vx;
    b->y += b->vy;
}


void reset_ball(ball *b) {
    b->x = (PLAYABLE_ZONE_WIDTH_START + PLAYABLE_ZONE_WIDTH-8)/2;
    b->y = PLAYABLE_ZONE_HEIGHT - 32 - 8;
    b->vx = 0;
    b->vy = 0;
}

void launch_ball(ball *b) {
    b->vy = -BALL_MAX_SPEED;
}
/*
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
}*/
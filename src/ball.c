#include "ball.h"
#include "collisions.h"
#include "constant.h"



ball create_ball() {
    ball result = {
        .x = 128 + 64,
        .y = SCREEN_HEIGHT - 16 - 24,
        .w = 24,
        .h = 24,
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

int ball_collision_bricks(ball *b, brick *bricks, int n) {
    int steps = fmax(abs(b->vx), abs(b->vy));
    float fx = (float)b->x;
    float fy = (float)b->y;

    for (int step = 0; step < steps; step++) {
        int collision = 0;
        float min_distance = INFINITY;
        int closest_brick_index = -1;

        // Predict the ball's future position
        SDL_Rect future_ball_rect = {(int)(fx + b->vx / steps), (int)(fy + b->vy / steps), b->w, b->h};

        for (int i = 0; i < n; i++) {
            if (bricks[i].health == 0 ) continue; // Skip the brick if it's not active

            SDL_Rect brick_rect = {bricks[i].x, bricks[i].y, bricks[i].w, bricks[i].h};

            if (SDL_HasIntersection(&future_ball_rect, &brick_rect)) {
                // Calculate the distance from the ball to the brick
                float dx = fx + b->w / 2 - (bricks[i].x + bricks[i].w / 2);
                float dy = fy + b->h / 2 - (bricks[i].y + bricks[i].h / 2);
                float distance = sqrt(dx * dx + dy * dy);

                // If this brick is closer than the current closest brick, update the closest brick
                if (distance < min_distance) {
                    min_distance = distance;
                    closest_brick_index = i;
                }
            }
        }

        if (closest_brick_index != -1) {
            // Determine the collision edge and adjust the ball's velocity
            SDL_Rect intersect_rect;
            SDL_IntersectRect(&future_ball_rect, &(SDL_Rect){bricks[closest_brick_index].x, bricks[closest_brick_index].y, bricks[closest_brick_index].w, bricks[closest_brick_index].h}, &intersect_rect);
            if (intersect_rect.w >= intersect_rect.h) {
                // Collision on vertical edge
                b->vy = -b->vy;
            } else {
                // Collision on horizontal edge
                b->vx = -b->vx;
            }

            damage_brick(&bricks[closest_brick_index]);
            collision = 1;
        }

        // Move the ball
        fx += (float)b->vx / steps;
        fy += (float)b->vy / steps;

        if (collision) {
            break;
        }
    }

    b->x = (int)roundf(fx);
    b->y = (int)roundf(fy);

    return 0;
}
void move_ball(ball *b, paddle *p, brick *bricks, int n) {
    ball new_ball = *b;

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

    ball_collision_bricks(b, bricks, n);
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

void reset_ball(ball *b) {
    b->x = 128 + 64;
    b->y = SCREEN_HEIGHT - 16 - 24;
    b->vx = 0;
    b->vy = 0;
}

void launch_ball(ball *b) {
    b->vy = -BALL_MAX_SPEED;
}

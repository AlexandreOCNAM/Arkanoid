#include "ball.h"
#include "constant.h"


#define MAX_SPEED 7
#define ZONE_SIZE SCREEN_HEIGHT / 4



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

void ball_collision_bricks(ball *b, brick *bricks, int n) {
    int steps = fmax(abs(b->vx), abs(b->vy));

    for (int step = 0; step < steps; step++) {
        int collision;
        do {
            collision = 0;
            float min_distance = INFINITY;
            int closest_brick_index = -1;

            // Determine the zone of the ball
            int zone_x = b->x / (PLAYABLE_ZONE_WIDTH / 2);
            int zone_y = b->y / (PLAYABLE_ZONE_HEIGHT / 2);

            // Predict the ball's future position
            SDL_Rect future_ball_rect = {b->x + b->vx / steps, b->y + b->vy / steps, b->w, b->h};

            for (int i = 0; i < n; i++) {
                // Check if the brick is in the same zone as the ball
                if (bricks[i].health > 0 && bricks[i].x / (PLAYABLE_ZONE_WIDTH / 2) == zone_x && bricks[i].y / (PLAYABLE_ZONE_HEIGHT / 2) == zone_y) {
                    SDL_Rect brick_rect = {bricks[i].x, bricks[i].y, bricks[i].w, bricks[i].h};
                    if (SDL_HasIntersection(&future_ball_rect, &brick_rect)) {
                        // Calculate the distance from the ball to the brick
                        float dx = b->x + b->w / 2 - (bricks[i].x + bricks[i].w / 2);
                        float dy = b->y + b->h / 2 - (bricks[i].y + bricks[i].h / 2);
                        float distance = sqrt(dx * dx + dy * dy);

                        // If this brick is closer than the current closest brick, update the closest brick
                        if (distance < min_distance) {
                            min_distance = distance;
                            closest_brick_index = i;
                        }
                    }
                }
            }

            if (closest_brick_index != -1) {
                // Determine the collision point
                float collisionX = b->x + b->w / 2;
                float collisionY = b->y + b->h / 2;

                // Determine the collision edge
                if (collisionX <= bricks[closest_brick_index].x || collisionX >= bricks[closest_brick_index].x + bricks[closest_brick_index].w) {
                    // Collision on vertical edge
                    b->vx = -b->vx;
                } else if (collisionY <= bricks[closest_brick_index].y || collisionY >= bricks[closest_brick_index].y + bricks[closest_brick_index].h) {
                    // Collision on horizontal edge
                    b->vy = -b->vy;
                } else {
                    // Collision at corner
                    b->vx = -b->vx;
                    b->vy = -b->vy;
                }

                damage_brick(&bricks[closest_brick_index]);
                collision = 1;
            }

            // Move the ball
            b->x += b->vx / steps;
            b->y += b->vy / steps;
        } while (collision);
    }
}
void move_ball(ball *b, paddle *p, brick *bricks, int n) {


    if (b->x < 0 || b->x > PLAYABLE_ZONE_WIDTH - b->w) {
        b->vx = -b->vx;
    }
    if (b->y < 0 || b->y > PLAYABLE_ZONE_HEIGHT - b->h) {
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

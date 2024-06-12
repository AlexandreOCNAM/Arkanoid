#include "ball.h"


#define MAX_SPEED 7
#define ZONE_SIZE SCREEN_HEIGHT / 4



void create_ball(ball *b) {
    ball result = {
        .x = (PLAYABLE_ZONE_WIDTH_START + PLAYABLE_ZONE_WIDTH-8)/2,
        .y = PLAYABLE_ZONE_HEIGHT - 32 - 8,
        .w = 8.99f,
        .h = 8.99,
        .vx = 0,
        .vy = 0,
        .rect = malloc(sizeof(SDL_Rect)),
        .active = 1,
        .is_catch = 1,
    };
    result.rect->x = result.x;
    result.rect->y = result.y;
    result.rect->w = result.w;
    result.rect->h = result.h;
    *b = result;
}

int move_balls(ball **balls, int *balls_count, paddle *p, brick *bricks, int n, level *l, droid *droids, int droid_count) {

    for (int i=0; i < *balls_count; i++){
        if(balls[i]->active == 1){
            move_ball(balls[i], p, bricks, n, droids, droid_count);
        }
    }
    for (int i=0; i< *balls_count; i++){
        if(balls[i]->active == 0){
            printf("Ball to remove: %d\n", i);
            // shift the balls array
            for (int j=i; j< *balls_count-1; j++){
                balls[j] = balls[j+1];
                printf("Ball %d shifted with %d, old active: %d -> new active: %d\n", j, j+1, balls[j]->active, balls[j+1]->active);
            }
            *balls_count -= 1;
        }
    }
    if (*balls_count == 0){
        l->is_playing = 0;
        l->is_started = 0;
        l->lives -= 1;
        reset_balls(balls, balls_count);
        *p = create_paddle(p->w);
        return 0;
    }
    return 1;
}

void move_ball(ball *b, paddle *p, brick *bricks, int n, droid *droids, int droid_count) {
    if (b->is_catch){
        b->x = p->x + p->w/2 - b->w/2;
        b->y = p->y - b->h;
        return;
    }

    if(b->active == 1) {
        int killed = 0;
        if (b->x < PLAYABLE_ZONE_WIDTH_START || b->x > PLAYABLE_ZONE_WIDTH - b->w) {
            b->vx = -b->vx;
        }
        if (b->y < PLAYABLE_ZONE_HEIGHT_START) {
            b->vy = -b->vy;
        }
        else if (b->y > PLAYABLE_ZONE_HEIGHT - b->h){
            b->active = 0;
        }

        for (int i = 0; i < n; i++) {
            if (bricks[i].health > 0 || bricks[i].health == -1) {
                if (b->x < bricks[i].x + bricks[i].w &&
                    b->x + b->w > bricks[i].x &&
                    b->y < bricks[i].y + bricks[i].h &&
                    b->y + b->h > bricks[i].y) {

                    // Calculate the closest point on the AABB to the circle's center
                    float closestX = fmax(bricks[i].x, fmin(b->x, bricks[i].x + bricks[i].w));
                    float closestY = fmax(bricks[i].y, fmin(b->y, bricks[i].y + bricks[i].h));

                    // Calculate the distance between the circle's center and this point
                    float distanceX = b->x - closestX;
                    float distanceY = b->y - closestY;
                    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                    // If the distance is less than the circle's radius, there is a collision
                    if (distanceSquared < (b->w / 2 * b->w / 2)) {
                        // collision detected!
                        // Determine if it's a corner or side collision
                        if (closestX == bricks[i].x || closestX == bricks[i].x + bricks[i].w ||
                            closestY == bricks[i].y || closestY == bricks[i].y + bricks[i].h) {
                            // It's a corner collision
                            b->vx = -b->vx;
                            b->vy = -b->vy;
                        } else {
                            // It's a side collision
                            if (distanceX < distanceY) {
                                b->vx = -b->vx;
                            } else {
                                b->vy = -b->vy;
                            }
                        }

                        damage_brick(&bricks[i]);
                        return;
                    }
                }
            }
        }

        for (int i = 0; i < droid_count; i++) {
            if (droids[i].health > 0 && droids[i].active == 1) {
                if (b->x < droids[i].x + droids[i].w &&
                    b->x + b->w > droids[i].x &&
                    b->y < droids[i].y + droids[i].h &&
                    b->y + b->h > droids[i].y) {

                    // Handle the collision
                    float top = fabs(b->y + b->h - droids[i].y);
                    float bottom = fabs(droids[i].y + droids[i].h - b->y);
                    float left = fabs(b->x + b->w - droids[i].x);
                    float right = fabs(droids[i].x + droids[i].w - b->x);

                    float min = fmin(fmin(fmin(top, bottom), left), right);

                    if (min == top || min == bottom) {
                        b->vy = -b->vy;
                    } else {
                        b->vx = -b->vx;
                    }

                    // Reduce the brick's health
                    damage_droid(&droids[i]);
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
            if (p->catch_ball){
                b->is_catch = 1;
                return;
            }

        }
        b->x += b->vx;
        b->y += b->vy;
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

void set_ball_speed(ball *b, int vx, int vy){
    b->vx = fmax(1, vx);
    b->vy = fmax(1, vy);
}


void reset_balls(ball **balls, int *ball_count) {
    free(balls);
    balls = malloc(sizeof(ball*));
    *ball_count = 1;
    balls[0] = malloc(sizeof(ball));
    create_ball(balls[0]);
}

void launch_ball(ball *b) {
    if(b->active) {
        b->vy = -BALL_MAX_SPEED;
        b->is_catch = 0;
    }
}


void split_balls(ball** balls, int *ball_count) {
    ball **new_balls = malloc(sizeof(ball*) * (*ball_count * 2));
    for (int i=0; i< *ball_count; i++){
        new_balls[i] = malloc(sizeof(ball));
        memcpy(new_balls[i], balls[i], sizeof(ball));
        new_balls[i+*ball_count] = malloc(sizeof(ball));
        memcpy(new_balls[i+*ball_count], balls[i], sizeof(ball));
        new_balls[i+*ball_count]->vx = -balls[i]->vx;
    }
    *ball_count *= 2;
    memcpy(balls, new_balls, sizeof(ball*) * (*ball_count));
    free(new_balls);
}

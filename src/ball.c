#include "ball.h"


#define MAX_SPEED 7
#define ZONE_SIZE SCREEN_HEIGHT / 4



void create_ball(ball *b) {
    ball result = {
        .x = (PLAYABLE_ZONE_WIDTH_START + PLAYABLE_ZONE_WIDTH-8)/2,
        .y = PLAYABLE_ZONE_HEIGHT - 32 - 8,
        .w = 8,
        .h = 8,
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
//    int all_killed = 0;
//    for (int i = 0; i < balls_count; i++) {
//        all_killed += move_ball(&balls[i], p, bricks, n);
//        if(all_killed == balls_count) {
//            reset_balls(&balls[i], balls_count);
//            reset_paddle(p, srcVaiss[0].w);
//            l->is_playing = 0;
//            l->lives -= 1;
//            return 1;
//        }
//        else{
//            return 0;
//        }
//    }
    for (int i=0; i < *balls_count; i++){
        if(balls[i]->active == 1){
            move_ball(balls[i], p, bricks, n, droids, droid_count);
        }
    }
    int count = 0;
    for (int i=0; i< *balls_count; i++){
        if (balls[i]->active == 1){
            count++;
        }
    }
    ball ** new_balls = malloc(sizeof(ball*) * count);
    int j = 0;
    for (int i=0; i< *balls_count; i++){
        if (balls[i]->active == 1){
            new_balls[j] = balls[i];
            j++;
        }
    }
    free(balls);
    balls = malloc(sizeof(ball*) * count);
    memcpy(balls, new_balls, sizeof(ball*) * count);
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
    b->vx = vx;
    b->vy = vy;
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
        b->is_catch = 1;
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
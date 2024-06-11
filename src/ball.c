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
        .rect = malloc(sizeof(SDL_Rect)),
        .active = 1
    };
    result.rect->x = result.x;
    result.rect->y = result.y;
    result.rect->w = result.w;
    result.rect->h = result.h;
    return result;
}

void move_balls(ball *balls, int balls_count, paddle *p, brick *bricks, int n, level *l){
    int all_killed = 0;
    for (int i = 0; i < balls_count; i++) {
        all_killed += move_ball(&balls[i], p, bricks, n, &l);
        if(all_killed == balls_count) {
            reset_balls(&balls[i], balls_count);
            reset_paddle(p, srcVaiss[0].w);
            l->is_playing = 0;
            l->lives -= 1;
        }
        else{

        }
    }
}

int move_ball(ball *b, paddle *p, brick *bricks, int n, level *l) {

    int killed = 0;
    if (b->x < PLAYABLE_ZONE_WIDTH_START || b->x > PLAYABLE_ZONE_WIDTH - b->w) {
        b->vx = -b->vx;
    }
    if (b->y < PLAYABLE_ZONE_HEIGHT_START) {
        b->vy = -b->vy;
    }
    else if (b->y > PLAYABLE_ZONE_HEIGHT - b->h){
        killed = 1;
        b->active = 0;
    }
    // Check for collision with bricks
    if(b->active == 1) {
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
    return killed;
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


void reset_balls(ball *balls, int ball_count) {
    balls[0].x = (PLAYABLE_ZONE_WIDTH_START + PLAYABLE_ZONE_WIDTH-8)/2;
    balls[0].y = PLAYABLE_ZONE_HEIGHT - 32 - 8;
    balls[0].vx = 0;
    balls[0].vy = 0;
    balls[0].active = 1;
    for(int i = 1; i == ball_count; i++){
        balls[i].active = 0;
        balls[i].vx = 0;
        balls[i].vy = 0;;
    }
}

void launch_ball(ball *b) {
    if(b->active)
        b->vy = -BALL_MAX_SPEED;
}

void slow_ball(ball *ball) {
        if (ball->vx > 1 && ball->vy > 1) {
            ball->vx = 1;
            ball->vy = 1;
        }
}

void split_ball(ball balls[], int *ball_count) {
    if (*ball_count < MAX_BALLS) {
        int i = 0;
        while(balls[i].active != 1){
            i++;
        }

        ball *original_ball = &balls[i];

        ball *new_ball1 = &balls[*ball_count];
        ball *new_ball2 = &balls[*ball_count + 1];

        *new_ball1 = *original_ball;
        *new_ball2 = *original_ball;

        new_ball1->vx = original_ball->vx;
        new_ball1->vy = -original_ball->vy;

        new_ball2->vx = -original_ball->vx;
        new_ball2->vy = original_ball->vy;

        *ball_count += 2;
    }
}
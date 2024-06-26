//
// Created by OfferleA on 5/30/2024.
//

#include "game.h"
#include "extractFile.h"
#include "graphics.h"
#include "constant.h"
#include "powerup.h"
#include "laser.h"
#include <time.h>


#define FPS 60
int default_paddle_width = 64;
int powerup_count = 0;
static time_t last_laser_time = 0;
static time_t last_slow_time = 0;
int score = 0;
PowerUp powerups[MAX_POWERUPS];

void reset_game_components(game_components *gc);

void fire_laser(laser lasers[10], int *pInt, paddle *ptr);

void move_lasers(laser lasers[10], int *pInt, brick *bricks, const int *n);

void init_game(game* g) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        perror("Error while initializing SDL");
        exit(1);
    }
    init_level(g, 1);
    init_window();
}

void init_level(game *g, int level_nu) {
    g->l = malloc(sizeof(level));
    create_level(g->l, level_nu);
    g->level_number = level_nu;
    g->gc = malloc(sizeof(game_components));
    g->gc->balls = malloc(sizeof(ball *));
    g->gc->balls[0] = malloc(sizeof(ball));
    create_ball(g->gc->balls[0]);
    g->gc->ball_count = 1;
    /*if(level_nu == 1)
        g->gc->p.w = default_paddle_width;*/
    g->gc->p = create_paddle(default_paddle_width);
    g->gc->laser_count = 0;

    for (int i= 0 ; i < MAX_DROIDS; i++) {
        create_droid(&g->gc->droids[i], rand()% PLAYABLE_ZONE_WIDTH_START, rand()% PLAYABLE_ZONE_HEIGHT/2);
    }
}

_Noreturn void play_game(game* g) {
    Uint64 prev = SDL_GetPerformanceCounter(), now = 0;
    while (1) {
        handle_input(g);
        update(g);
        now = SDL_GetPerformanceCounter();
        double delta_t = 1.0 / FPS - (double) (now - prev) / (double) SDL_GetPerformanceFrequency();
        update_bricks(delta_t);
        update_powerups(powerups, &powerup_count, delta_t, g->gc, (level *) &g->l->lives);
        render(g);
        prev = now;
        if (delta_t > 0) {
            SDL_Delay(delta_t * 1000);
        }
        prev = SDL_GetPerformanceCounter();
    }
}

void handle_input(game* g) {
    SDL_PumpEvents();
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_ESCAPE]) {
        stop_game(g);
    }
    if (keys[SDL_SCANCODE_SPACE]) {
        //if (keys[SDL_SCANCODE_SPACE]) {
        g->l->is_started = 1;
        g->l->is_playing = 1;
        if (g->gc->balls[0]->is_catch == 1)
        {
            launch_ball(g->gc->balls[0]);
            g->gc->p.catch_ball = 0;
        }
    }
    if (g->l->is_playing == 0 && g->gc->balls[0]->is_catch == 1) {
        if (keys[SDL_SCANCODE_LEFT]) {
            g->gc->balls[0]->vx = fmax(-BALL_MAX_SPEED, fmin(--g->gc->balls[0]->vx, BALL_MAX_SPEED));
        }
        else if (keys[SDL_SCANCODE_RIGHT] && g->gc->balls[0]->is_catch == 1) {
            g->gc->balls[0]->vx = fmax(-BALL_MAX_SPEED, fmin(++g->gc->balls[0]->vx, BALL_MAX_SPEED));
        }
    }
    else {
        if (keys[SDL_SCANCODE_LEFT] && g->l->is_playing) {
            // collision of the paddle with the left wall
            strafe_paddle(&g->gc->p, 0);
        } else if (keys[SDL_SCANCODE_RIGHT] && g->l->is_playing) {
            // collision of the paddle with the right wall
            strafe_paddle(&g->gc->p, 1);
        } else {
            g->gc->p.vx = 0;
        }
        if (keys[SDL_SCANCODE_LCTRL] && g->gc->p.has_laser) {
            if (g->gc->laser_count < MAX_LASERS) {
                fire_laser(g->gc->lasers, &g->gc->laser_count, &g->gc->p);
            }
        }
        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_T] && g->gc->p.has_laser) {
            g->gc->p.has_laser = 1;
        }
        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_R] ){
            fire_laser(g->gc->lasers, &g->gc->laser_count, &g->gc->p);
        }
    }
}

void fire_laser(laser lasers[10], int *pInt, paddle *ptr) {
    // Prevents the player from firing lasers too quickly, only one laser per second
    if (time(NULL) - last_laser_time < 1) {
        return;
    }
    create_laser(&lasers[*pInt], ptr->x + ptr->w / 2, ptr->y);
    ptr->has_laser = 0;
    *pInt += 1;
    last_laser_time = time(NULL);
}

void update(game *g) {
    int end = is_level_over(g->l);
    if (end == 1) {
        g->level_number += 1;

        reset_level(g->l);
        reset_game(g);
        create_level(g->l, g->level_number);
    }
    else if (end == -1) {
        end_game(g);
    }
    if (g->l->is_playing == 1) {
        int b_left = move_balls(g->gc->balls, &g->gc->ball_count, &g->gc->p, g->l->bricks, g->l->num_bricks, g->l, g->gc->droids, MAX_DROIDS);
//            int all_killed = move_balls(&g->gc->b, g->gc->ball_count, &g->gc->p, g->l->bricks, g->l->num_bricks, g->l);
        if(b_left == 0)
            powerup_count = 0;
        if (active_lasers(g->gc->lasers, &g->gc->laser_count)) {
            update_lasers(g->gc->lasers, &g->gc->laser_count, g->l->bricks, &g->l->num_bricks);
        }
    }
    update_droids(g->gc->droids, MAX_DROIDS, g->l->bricks, g->l->num_bricks);
}

void reset_game_components(game_components *gc) {
    reset_balls(gc->balls, &gc->ball_count);
    gc->ball_count = 1;
    powerup_count = 0;
    reset_paddle(&gc->p, srcVaiss[0].w);
    reset_droids(gc->droids, MAX_DROIDS);
}

void render(game *g) {
    blit_background();
    draw_balls(g->gc->balls, g->gc->ball_count);
    draw_paddle(&g->gc->p);
    draw_bricks(g->l->bricks, g->l->num_bricks);
    draw_powerups(powerups, powerup_count);
    draw_lasers(g->gc->lasers, g->gc->laser_count);
    draw_droids(g->gc->droids, MAX_DROIDS);
    write_score(score);
    write_lives(g->l->lives);
    update_window();
}

void stop_game(game *g) {
    SDL_Quit();
    exit(0);
}

void reset_game(game *g) {
    reset_game_components(g->gc);
    g->l->is_started = 0;
    SDL_Delay(1000);
    blit_background();
    update_window();
}

void end_game(game *g) {
    reset_game(g);
    reset_level(g->l);
    g->level_number = 1;
    score = 0;
    create_level(g->l, g->level_number);
    SDL_Delay(1000);
    blit_background();
    update_window();
}


void update_powerups(PowerUp powerups[], int *powerup_count, double delta_t, game_components *gc, level *l) {
    for (int i = 0; i < *powerup_count; i++) {
        PowerUp *pu = &powerups[i];
        if (pu->active) {
            pu->y += 2; // Descend le power-up
            SDL_Rect paddle_rect = {gc->p.x, gc->p.y, gc->p.w, gc->p.h};
            SDL_Rect powerup_rect = {pu->x, pu->y, pu->w, pu->h};
            if (SDL_HasIntersection(&paddle_rect, &powerup_rect)) {
                pu->active = 0;
                score += 1000;
                switch (pu->type) {
                    case EXPAND:
                        printf("Has catched EXPAND");
                        extend_paddle(&gc->p);
                        break;
                    case LASER:
                        printf("Has catched LASER");
                        gc->p.has_laser = 1;
                        break;
                    case BREAK:
                        for (int k = 0; k < l->num_bricks; k++) {
                            l->bricks[k].health = 0;
                        }
                        printf("Has catched BREAK\n");
                        break;
                    case PLAYER:
                        add_life(l);
                        printf("Has catched PLAYER");
                        break;
                    case SLOW:
                        printf("Has catched SLOW");
//                        for(int j = 0; j < gc->ball_count; j++){
//                            set_ball_speed(gc->balls[j], gc->balls[j]->vx/2.0f, gc->balls[j]->vy/2.0f);
//                            last_slow_time = time(NULL);
//                        }
                        break;
                    case DIVIDE:
                        printf("Has catched DIVIDE\n");
                        split_balls(gc->balls, &gc->ball_count);
                        break;
                    case CATCH:
                        printf("Has catched CATCH");
                        gc->balls[0]->is_catch = 1;
                        break;
                    default:
                        break;
                }
            }

            if (pu->y > SCREEN_HEIGHT) {
                pu->active = 0;
            }

            update_powerup_animation(pu, delta_t);
        }
    }
}
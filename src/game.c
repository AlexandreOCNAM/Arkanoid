//
// Created by OfferleA on 5/30/2024.
//

#include "game.h"
#include "extractFile.h"
#include "graphics.h"
#include "constant.h"
#include "powerup.h"


#define FPS 60
int default_paddle_width = 64;
int powerup_count = 0;



void reset_game_components(game_components *gc);

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
    g->gc->b[0] = create_ball();
    g->gc->ball_count = 1;
    /*if(level_nu == 1)
        g->gc->p.w = default_paddle_width;*/
    g->gc->p = create_paddle(default_paddle_width);
}

_Noreturn void play_game(game* g) {
    Uint64 prev = SDL_GetPerformanceCounter(), now = 0;
    while (1) {
        handle_input(g);
        update(g);
        now = SDL_GetPerformanceCounter();
        double delta_t = 1.0 / FPS - (double) (now - prev) / (double) SDL_GetPerformanceFrequency();
        update_bricks(delta_t);
        update_powerups(powerups, &powerup_count, &g->gc->p, delta_t, &g->gc->b, &g->gc->ball_count, &g->l->lives);
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
        launch_ball(&g->gc->b[0]);
    }
    if (g->l->is_started == 0) {
        if (keys[SDL_SCANCODE_LEFT]) {
            g->gc->b[0].vx = fmax(-BALL_MAX_SPEED, fmin(--g->gc->b[0].vx, BALL_MAX_SPEED));
        }
        else if (keys[SDL_SCANCODE_RIGHT]){
            g->gc->b[0].vx = fmax(-BALL_MAX_SPEED, fmin(++g->gc->b[0].vx, BALL_MAX_SPEED));
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
    }
}

void update(game *g) {
    if (g->l->is_started) {
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
        else {
            move_balls(&g->gc->b, g->gc->ball_count, &g->gc->p, g->l->bricks, g->l->num_bricks, g->l);
        }
    }
}

void reset_game_components(game_components *gc) {
    reset_balls(gc->b, gc->ball_count);
    gc->ball_count = 1;
    powerup_count = 0;
    reset_paddle(&gc->p, srcVaiss[0].w);
}

void render(game *g) {
    blit_background();
    draw_balls(&g->gc->b, g->gc->ball_count);
    draw_paddle(&g->gc->p);
    draw_bricks(g->l->bricks, g->l->num_bricks);
    draw_powerups(powerups, powerup_count);
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

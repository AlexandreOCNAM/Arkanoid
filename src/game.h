//
// Created by OfferleA on 5/30/2024.
//

#ifndef ARKANOID_GAME_H
#define ARKANOID_GAME_H

#include <stdbool.h>
#include <time.h>
#include "brick.h"
#include "ball.h"
#include "level.h"
#include "laser.h"


extern int score;
extern PowerUp powerups[MAX_POWERUPS];

#define MAX_LASERS 10  // Maximum number of lasers

typedef struct {
    ball **balls;
    int ball_count;
    paddle p;
    laser lasers[MAX_LASERS];  // Array of lasers
    int laser_count;  // Number of active lasers
} game_components;

typedef struct {
    int level_number;
    level *l;
    game_components *gc;
} game;

void init_game(game *g);

_Noreturn void play_game(game* g);
void handle_input(game* g);
void update(game* g);
void render(game* g);
void stop_game(game *g);
void reset_game(game* g);
void init_level(game *g, int level_nu);
void end_game(game *g);
void update_powerups(PowerUp powerups[], int *powerup_count, double delta_t, game_components *gc, level *l);


#endif //ARKANOID_GAME_H

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


int score;
PowerUp powerups[MAX_POWERUPS];


typedef struct {
    ball b[MAX_BALLS];
    int ball_count;
    paddle p;
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



#endif //ARKANOID_GAME_H

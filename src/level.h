//
// Created by OfferleA on 5/30/2024.
//

#ifndef ARKANOID_LEVEL_H
#define ARKANOID_LEVEL_H


#include "brick.h"

typedef struct {
    int score;
    int lives;
    int is_started;
    brick *bricks;
    int num_bricks;
} level;

void create_level(level *l, int level_number);
void reset_level(level *l);
void destroy_level(level *l);
int is_level_over(level *l);

#endif //ARKANOID_LEVEL_H

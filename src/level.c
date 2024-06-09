//
// Created by OfferleA on 5/30/2024.
//

#include "level.h"
#include "extractFile.h"

void create_level(level *l, int level_number) {
    l->lives = 3;
    l->is_started = 0;
    l->bricks = calloc(sizeof(brick), 256);

    char path[50] = {0};
    sprintf(path, "../Levels/niveau%d.txt", level_number);
    printf("Loading level from %s\n", path);
    load_level(path, l->bricks, &l->num_bricks, level_number);
}

int is_level_over(level *l) {
    if (l->lives <= 0) {
        puts("Game over");
        return -1;
    }
    for (int i = 0; i < l->num_bricks; i++) {
        if (l->bricks[i].health == -1) {
            continue;
        }
        if (l->bricks[i].health > 0) {
            return 0;
        }
    }

    puts("Level over");
    return 1;
}

void reset_level(level *l) {
    free(l->bricks);
    l->num_bricks = 0;
    l->is_started = 0;
}

void destroy_level(level *l) {
    free(l->bricks);
    free(l);
}

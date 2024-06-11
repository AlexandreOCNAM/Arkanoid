//
// Created by OfferleA on 6/11/2024.
//

#include "droid.h"
#include "constant.h"

static time_t last_droid_update = 0;

SDL_Rect srcDroid[8] = {
        {0, 256, 32, 32},
        {32, 256, 32, 32},
        {64, 256, 32, 32},
        {96, 256, 32, 32},
        {128, 256, 32, 32},
        {160, 256, 32, 32},
        {192, 256, 32, 32},
        {224, 256, 32, 32}
};

SDL_Rect srcDroidAtom[24] = {
        {0, 320, 32, 32},
        {32, 320, 32, 32},
        {64, 320, 32, 32},
        {96, 320, 32, 32},
        {128, 320, 32, 32},
        {160, 320, 32, 32},
        {192, 320, 32, 32},
        {224, 320, 32, 32},
        {256, 320, 32, 32},
        {288, 320, 32, 32},
        {320, 320, 32, 32},
        {352, 320, 32, 32},
        {384, 320, 32, 32},
        {416, 320, 32, 32},
        {448, 352, 32, 32},
        {480, 320, 32, 32},
        {0, 320, 32, 32},
        {32, 320, 32, 32},
        {64, 320, 32, 32},
        {96, 320, 32, 32},
        {128, 320, 32, 32},
        {160, 320, 32, 32},
        {192, 320, 32, 32},
        {224, 320, 32, 32}
};

SDL_Rect srcDroidGreen[11] = {
        {0, 288, 32, 32},
        {32, 288, 32, 32},
        {64, 288, 32, 32},
        {96, 288, 32, 32},
        {128, 288, 32, 32},
        {160, 288, 32, 32},
        {192, 288, 32, 32},
        {224, 288, 32, 32},
        {256, 288, 32, 32},
        {288, 288, 32, 32},
        {320, 288, 32, 32}
};

SDL_Rect srcDroidDeath[6] = {
        {0,   384, 32, 32},
        {32,  384, 32, 32},
        {64,  384, 32, 32},
        {96,  384, 32, 32},
        {128, 384, 32, 32},
        {160, 384, 32, 32}
};


void create_droid(droid *d, int x, int y) {
    d->x = x + 50;
    d->y = y + 50;
    d->w = 32;
    d->h = 32;
    d->vx = 2;
    d->vy = 2;
    d->srcRect = srcDroid[0];
    d->active = rand() % 2;
    d->frame_nu = 0;
    d->health = 1;
    d->type = rand() % 3;
}

void update_droid(droid *d) {
    if (d->health > 0 && d->active == 1) {
        d->vx = rand() % 3 - 1 * rand() % 2 == 0 ? 1 : -1;
        d->vy = rand() % 3 - 1 * rand() % 2 == 0 ? 1 : -1;
        if (d->type == 0) {
            d->frame_nu = (d->frame_nu + 1) % DROID_BLUE_MAX_FRAME;
            d->srcRect = srcDroid[d->frame_nu];
            // if the droid is in the lower half of the screen, move it up to the top half
            if (d->y > PLAYABLE_ZONE_HEIGHT / 2) {
                d->vy = -d->vy;
            }

        } else if (d->type == 1) {
            d->frame_nu = (d->frame_nu + 1) % DROID_ATOM_MAX_FRAME;
            d->srcRect = srcDroidAtom[d->frame_nu];
            if (d->frame_nu == DROID_ATOM_MAX_FRAME - 1) {
                d->active = 0;
            }
        } else {
            d->frame_nu = (d->frame_nu + 1) % DROID_GREEN_MAX_FRAME;
            d->srcRect = srcDroidGreen[d->frame_nu];
        }
    }
    else {
        d->frame_nu = (d->frame_nu + 1) % DROID_DEATH_MAX_FRAME;
        d->srcRect = srcDroidDeath[d->frame_nu];
        if (d->frame_nu == DROID_DEATH_MAX_FRAME - 1) {
            d->active = 0;
        }
    }

}

void update_droids(droid *droids, int droid_count, brick *bricks, int brick_count) {
    time_t now = time(NULL);
    if (now - last_droid_update > 1/60) {
        last_droid_update = now;
        for (int i = 0; i < droid_count; i++) {
            if (droids[i].active == 1) {
                update_droid(&droids[i]);
            }
        }
    }
    for (int i = 0; i < droid_count; i++) {
        if (droids[i].active == 1 && droids[i].health > 0) {
            move_droid(&droids[i], bricks, brick_count);
        }
    }
}

void move_droid(droid *d, brick *bricks, int brick_count) {
    d->x += d->vx;
    d->y += d->vy;
    if (d->x < PLAYABLE_ZONE_WIDTH_START) {
        d->x = PLAYABLE_ZONE_WIDTH_START;
        d->vx = -d->vx;
    }
    if (d->x + d->w > PLAYABLE_ZONE_WIDTH) {
        d->x = PLAYABLE_ZONE_WIDTH - d->w;
        d->vx = -d->vx;
    }
    if (d->y < PLAYABLE_ZONE_HEIGHT_START) {
        d->y = PLAYABLE_ZONE_HEIGHT_START;
        d->vy = -d->vy;
    }
    if (d->y + d->h > PLAYABLE_ZONE_HEIGHT) {
        d->y = PLAYABLE_ZONE_HEIGHT - d->h;
        d->vy = -d->vy;
    }
    if (d->type != 0){
        for (int i = 0; i < brick_count; i++) {
            if (bricks[i].health > 0) {
                if (d->x < bricks[i].x + bricks[i].w &&
                    d->x + d->w > bricks[i].x &&
                    d->y < bricks[i].y + bricks[i].h &&
                    d->y + d->h > bricks[i].y) {
                    d->vx = -d->vx;
                    d->vy = -d->vy;
                    break;
                }
            }
        }
    }
}

void damage_droid(droid *d) {
    d->health--;
    if (d->health == 0) {
        d->frame_nu = 0;
    }
}

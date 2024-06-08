//
// Created by OfferleA on 5/28/2024.
//

#include "brick.h"
#include "game.h"

static int timeAccumulator = 0;
static int goldenBrickState = 0;
static int silverBrickState = 0;

void create_brick(brick *brick, int x, int y, int width, int height, int health, int points) {
    brick->x = x + PLAYABLE_ZONE_WIDTH_START;
    brick->y = y + PLAYABLE_ZONE_HEIGHT_START;
    brick->w = width;
    brick->h = height;
    brick->health = health;
    brick->points = points;
    //printf("Created brick at (%d, %d) with health %d\n", x, y, health);
}


int damage_brick(brick *b) {
    if (b->health == -1) {
        return -1;
    }
    b->health = fmax(0, b->health - 1);
    if (b->health == 0) {
        score += b->points;
        if (b->powerup.type != NONE) {
            //printf("Power-Up initialized : %d\n", b->powerup.type);
            PowerUp *pu = &powerups[powerup_count];
            pu->type = b->powerup.type;
            pu->x = b->x;
            pu->y = b->y;
            pu->w = b->w;
            pu->h = b->h;
            pu->srcRect = b->powerup.srcRect;
            pu->active = 1;
            (powerup_count)++;
        }
    }
}

int is_brick_dead(brick *b) {
    return b->health == 0;
}

int is_brick_breakable(brick *b) {
    return b->health == -1;
}

void update_bricks(double delta_t) {
    if(delta_t > 0)
        timeAccumulator += delta_t*1000;
    if (timeAccumulator >= 5000) {
        int frame = (int)((timeAccumulator - 5000) / 100) % 6;

        goldenBrickState = frame;
        silverBrickState = frame;

        if (timeAccumulator >= 5500) {  // Réinitialiser après 6 secondes
            timeAccumulator = 0;
            goldenBrickState = 0;
            silverBrickState = 0;
        }
        // Impression de débogage
//        printf("Animating bricks: frame %d, timeAccumulator: %f\n", frame, timeAccumulator);
    }

}

SDL_Rect get_brick_rect(brick *b) {
    if (b->isGold) {
        return goldenBrickStates[goldenBrickState];
    }
    if (b->isSilver) {
        return silverBrickStates[silverBrickState];
    }
    return b->srcRect;
}

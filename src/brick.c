//
// Created by OfferleA on 5/28/2024.
//

#include "brick.h"

void damage_brick(brick *b) {
    b->health--;
    if (b->health == 0) {
        b->powerup = create_powerup(b->x, b->y);
    }
}

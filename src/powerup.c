//
// Created by OfferleA on 5/29/2024.
//

#include <stdlib.h>
#include "powerup.h"

PowerUp create_powerup(int x, int y) {
    PowerUp result = {
            .x = x,
            .y = y,
            .w = 20,
            .h = 20,
            .type = rand() % 3,
            .active = 1
    };
    return result;
}

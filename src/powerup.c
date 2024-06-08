//
// Created by OfferleA on 5/29/2024.
//

#include <stdlib.h>
#include "powerup.h"


PowerUp create_powerup(int x, int y) {
    PowerUp result = {
            .x = x,
            .y = y,
            .w = 32,
            .h = 16,
            .type = rand() % 3,
            .active = 1
    };
    return result;
}

void update_powerups(PowerUp powerups[], int *powerup_count, paddle *p) {
    for (int i = 0; i < *powerup_count; i++) {
        PowerUp *pu = &powerups[i];
        if (pu->active) {
            pu->y += 5; // Descend le power-up
            SDL_Rect paddle_rect = {p->x, p->y, p->w, p->h};
            SDL_Rect powerup_rect = {pu->x, pu->y, pu->w, pu->h};

            if (SDL_HasIntersection(&paddle_rect, &powerup_rect)) {
                pu->active = 0;
                switch (pu->type) {
                    case EXPAND:
                        p->w *= 2;
                        break;
                    case LASER:
                        p->w /= 2;
                        break;
                    case BREAK:
                        // Passer au niveau suivant
                        break;
                    case PLAYER:
                        // Ajouter une vie au joueur
                        break;
                    case SLOW:
                        // Augmenter la vitesse de la balle
                        break;
                    case DIVIDE:
                        // Diviser la balle
                        break;
                    case CATCH:
                        // Rendre la palette collante
                        break;
                    default:
                        break;
                }
            }

            if (pu->y > SCREEN_HEIGHT) {
                pu->active = 0; // Désactiver le power-up s'il sort de l'écran
            }
        }
    }
}

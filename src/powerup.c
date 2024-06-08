//
// Created by OfferleA on 5/29/2024.
//

#include <stdlib.h>
#include "powerup.h"
static int timeAccumulator = 0;


PowerUp create_powerup(int x, int y, PowerUpType type) {
    SDL_Rect rect;
    switch(type){
        case EXPAND:
            rect = E_bonus_states[0];
            break;
        case LASER:
            rect = L_bonus_states[0];
            break;
        case BREAK:
            rect = B_bonus_states[0];
            break;
        case PLAYER:
            rect = P_bonus_states[0];
            break;
        case SLOW:
            rect = S_bonus_states[0];
            break;
        case DIVIDE:
            rect = D_bonus_states[0];
            break;
        case CATCH:
            rect = C_bonus_states[0];
            break;
    }

    PowerUp result = {
            .x = x,
            .y = y,
            .w = 32,
            .h = 16,
            .srcRect = rect,
            .type = type,
            .active = 0,
            .current_state = 0
    };
    return result;
}

void update_powerups(PowerUp powerups[], int *powerup_count, paddle *p, double delta_t) {
    for (int i = 0; i < *powerup_count; i++) {
        PowerUp *pu = &powerups[i];
        if (pu->active) {
            pu->y += 2; // Descend le power-up
            SDL_Rect paddle_rect = {p->x, p->y, p->w, p->h};
            SDL_Rect powerup_rect = {pu->x, pu->y, pu->w, pu->h};
/*
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
            }*/

            if (pu->y > SCREEN_HEIGHT) {
                pu->active = 0;
            }

            update_powerup_animation(pu, delta_t);
        }
    }
}


void update_powerup_animation(PowerUp *pu, double delta_t) {
    if(delta_t > 0)
        timeAccumulator += delta_t*1000;

    if (pu->active) {
        pu->current_state = (int)(timeAccumulator / 200) % 6;
        switch (pu->type) {
            case EXPAND:
                pu->srcRect = E_bonus_states[pu->current_state];
                break;
            case LASER:
                pu->srcRect = L_bonus_states[pu->current_state];
                break;
            case BREAK:
                pu->srcRect = B_bonus_states[pu->current_state];
                break;
            case PLAYER:
                pu->srcRect = P_bonus_states[pu->current_state];
                break;
            case SLOW:
                pu->srcRect = S_bonus_states[pu->current_state];
                break;
            case DIVIDE:
                pu->srcRect = D_bonus_states[pu->current_state];
                break;
            case CATCH:
                pu->srcRect = C_bonus_states[pu->current_state];
                break;
            case NONE:
            default:
                break;
        }
    }
}
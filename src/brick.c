//
// Created by OfferleA on 5/28/2024.
//

#include "brick.h"
#include "spriteConstant.h"
#include <SDL2/SDL.h>


static double timeAccumulator;
static int goldenBrickCurrentState = 0;
static int silverBrickCurrentState = 0;

void create_brick(brick *brick, int x, int y, int width, int height, int health) {
    brick->x = x;
    brick->y = y;
    brick->w = width;
    brick->h = height;
    brick->health = health;
    //printf("Created brick at (%d, %d) with health %d\n", x, y, health);
    // Initialiser srcRect pour les briques dorées et argentées
    if (health > 100) {  // Exemple: 2 pour dorée, ajustez selon votre logique
        brick->srcRect = goldenBrickStates[0];
    } else if (health >= 2) {  // Exemple: 1 pour argentée, ajustez selon votre logique
        brick->srcRect = silverBrickStates[0];
    }
}


void damage_brick(brick *b) {
    b->health--;
}


void animateBricks(double delta_t) {
    printf("dt = %lf\n",delta_t*1000);
    printf("Time accumulator: %f ms\n", timeAccumulator);
    if(delta_t > 0)
        timeAccumulator += delta_t*1000;


    // Animer toutes les 5 secondes
    if (timeAccumulator >= 5000) {
        int frame = (int)((timeAccumulator - 5000) / 100) % 6;  // 6 états, changer toutes les 200 ms

        goldenBrickCurrentState = frame;
        silverBrickCurrentState = frame;

        if (timeAccumulator >= 5500) {  // Réinitialiser après 6 secondes
            timeAccumulator = 0;
            goldenBrickCurrentState = 0;
            silverBrickCurrentState = 0;
        }
        // Impression de débogage
        printf("Animating bricks: frame %d, timeAccumulator: %f\n", frame, timeAccumulator);
    }

}

SDL_Rect getBrickSrcRect(brick *b) {
    if (b->health > 100) {  // Exemple: 2 pour dorée, ajustez selon votre logique
        return goldenBrickStates[goldenBrickCurrentState];
    } else if (b->health >= 2) {  // Exemple: 1 pour argentée, ajustez selon votre logique
        return silverBrickStates[silverBrickCurrentState];
    } else {
        return b->srcRect;  // Autres types de briques
    }
}
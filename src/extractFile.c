#include "extractFile.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BRICK_WIDTH 32
#define BRICK_HEIGHT 16
#define BRICKS_PER_ROW 13

SDL_Rect get_brick_src_rect(int brick_number) {
    SDL_Rect srcRect;
    switch (brick_number) {
        case 1:
            srcRect = (SDL_Rect){0, 0, 32, 16}; // Brique blanche
            break;
        case 2:
            srcRect = (SDL_Rect){32, 0, 32, 16}; // Brique orange
            break;
        case 3:
            srcRect = (SDL_Rect){64, 0, 32, 16}; // Brique cyan
            break;
        case 4:
            srcRect = (SDL_Rect){96, 0, 32, 16}; // Brique vert clair
            break;
        case 5:
            srcRect = (SDL_Rect){128, 0, 32, 16}; // Brique bleu foncé
            break;
        case 6:
            srcRect = (SDL_Rect){160, 0, 32, 16}; // Brique vert foncé
            break;
        case 7:
            srcRect = (SDL_Rect){0, 16, 32, 16}; // Brique rouge clair
            break;
        case 8:
            srcRect = (SDL_Rect){32, 16, 32, 16}; // Brique bleu
            break;
        case 9:
            srcRect = (SDL_Rect){64, 16, 32, 16}; // Brique rose
            break;
        case 10:
            srcRect = (SDL_Rect){96, 16, 32, 16}; // Brique jaune
            break;
        case 11:
            srcRect = (SDL_Rect){128, 16, 32, 16}; // Brique rouge foncé
            break;
        case 12:
            srcRect = (SDL_Rect){160, 16, 32, 16}; // Brique cyan foncé
            break;
        case 20:
            srcRect = (SDL_Rect){0, 32, 32, 16}; // Brique argent
            break;
        case 30:
            srcRect = (SDL_Rect){0, 48, 32, 16}; // Brique or
            break;
        default:
            srcRect = (SDL_Rect){0, 0, 0, 0}; // Valeur par défaut si non valide
            break;
    }
    return srcRect;
}

void load_level(const char *filename, Brick bricks[], int *brick_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open level file\n");
        exit(1);
    }

    char line[256];
    int y = 0;
    int x = 0;
    *brick_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\n') {
            x++;
            if (x >= BRICKS_PER_ROW) {
                x = 0;
                y++;
            }
            continue; // Ignore les lignes vides
        }

        int brick_type;
        int brick_number;
        if (sscanf(line, "%dx%d", &brick_type, &brick_number) == 2) {
            SDL_Rect srcRect = get_brick_src_rect(brick_number);
            int brick_health;
            if(brick_type == 0){
                brick_health = 1;
            }
            else if(brick_type == 1){
                brick_health = 2;
            }
            else{
                brick_health = 999999;
            }

            if (srcRect.w > 0 && srcRect.h > 0) {
                Brick *brick = &bricks[*brick_count];
                create_brick(brick, x * BRICK_WIDTH, y * BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT, brick_health);
                brick->srcRect = srcRect; // Définit le rectangle source basé sur le numéro
                (*brick_count)++;
                printf("Placed brick of type '%dx%d' at (%d, %d), with PV = %d\n", brick_type, brick_number, x * BRICK_WIDTH, y * BRICK_HEIGHT, brick_health); // Message de débogage
            }
        }

        x++;
        if (x >= BRICKS_PER_ROW) {
            x = 0;
            y++;
        }
    }

    fclose(file);
}

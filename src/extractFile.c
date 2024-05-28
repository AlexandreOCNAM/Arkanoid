//
// Created by Sebastien on 20/03/2024.
//
#include "../includes/extractFile.h"

#define BRICK_WIDTH 32
#define BRICK_HEIGHT 16

SDL_Rect get_brick_src_rect(int brick_type) {
    SDL_Rect srcRect;
    switch (brick_type) {
        case '1':
            srcRect = (SDL_Rect){0, 0, 32, 16}; // Brique blanche
            break;
        case '2':
            srcRect = (SDL_Rect){32, 0, 32, 16}; // Brique orange
            break;
        case '3':
            srcRect = (SDL_Rect){64, 0, 32, 16}; // Brique cyan
            break;
        case '4':
            srcRect = (SDL_Rect){96, 0, 32, 16}; // Brique vert clair
            break;
        case '5':
            srcRect = (SDL_Rect){128, 0, 32, 16}; // Brique bleu foncé
            break;
        case '6':
            srcRect = (SDL_Rect){162, 0, 32, 16}; // Brique vert foncé

            break;
            // Ajoutez d'autres cas pour d'autres briques si nécessaire
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
    *brick_count = 0;

    while (fgets(line, sizeof(line), file)) {
        int len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        for (int x = 0; x < len; x++) {
            if (line[x] >= '1' && line[x] <= '6') { // Assurez-vous que le caractère est un chiffre valide
                Brick *brick = &bricks[*brick_count];
                brick_init(brick, x * 32, y * 16, 32, 16); // Positionne et dimensionne la brique
                brick->destroyed = false;
                brick->srcRect = get_brick_src_rect(line[x]); // Définit le rectangle source basé sur le chiffre
                (*brick_count)++;
            }
        }
        y++;
    }

    fclose(file);
}
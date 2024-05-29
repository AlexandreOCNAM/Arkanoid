//
// Created by Sebastien on 20/03/2024.
//
#include "extractFile.h"

#define BRICK_WIDTH 32
#define BRICK_HEIGHT 16

SDL_Rect get_brick_src_rect(int brick_type) {
    SDL_Rect srcRect;
    switch (brick_type) {
        case 'w':
            srcRect = (SDL_Rect){0, 0, 32, 16}; // Brique blanche
            break;
        case 'o':
            srcRect = (SDL_Rect){32, 0, 32, 16}; // Brique orange
            break;
        case 'c':
            srcRect = (SDL_Rect){64, 0, 32, 16}; // Brique cyan
            break;
        case 'g':
            srcRect = (SDL_Rect){96, 0, 32, 16}; // Brique vert clair
            break;
        case 'B':
            srcRect = (SDL_Rect){128, 0, 32, 16}; // Brique bleu foncé
            break;
        case 'G':
            srcRect = (SDL_Rect){160, 0, 32, 16}; // Brique vert foncé
            break;
        case 'r':
            srcRect = (SDL_Rect){0, 16, 32, 16}; // Brique rouge clair
            break;
        case 'b':
            srcRect = (SDL_Rect){32, 16, 32, 16}; // Brique bleu
            break;
        case 'p':
            srcRect = (SDL_Rect){64, 16, 32, 16}; // Brique rose
            break;
        case 'y':
            srcRect = (SDL_Rect){96, 16, 32, 16}; // Brique vert clair
            break;
        case 'R':
            srcRect = (SDL_Rect){128, 16, 32, 16}; // Brique rouge foncé
            break;
        case 'C':
            srcRect = (SDL_Rect){160, 16, 32, 16}; // Brique cyan foncé
            break;
        case 'A':
            srcRect = (SDL_Rect){0, 32, 32, 16}; // Brique argent
            break;
        case 'O':
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
    *brick_count = 0;

    while (fgets(line, sizeof(line), file)) {
        int len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        for (int x = 0; x < len; x++) {
            if (line[x] != ' ' && line[x] != '\n') {
                SDL_Rect srcRect = get_brick_src_rect(line[x]);
                if (srcRect.w > 0 && srcRect.h > 0) {
                    Brick *brick = &bricks[*brick_count];
                    create_brick(brick, x * 32, y * 16, 32, 16, 2); // Positionne et dimensionne la brique
                    brick->srcRect = srcRect; // Définit le rectangle source basé sur le caractère
                    (*brick_count)++;
                    printf("Placed brick of type '%c' at (%d, %d)\n", line[x], x * 32, y * 16); // Message de débogage

                }
            }
        }
        y++;
    }

    fclose(file);
}

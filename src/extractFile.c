#include "extractFile.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BRICK_WIDTH 32
#define BRICK_HEIGHT 16
#define BRICKS_PER_ROW 13

int brick_points;

//Bricks
SDL_Rect whiteBrick = {0, 0, 32, 16};
SDL_Rect orangeBrick = {32, 0, 32, 16};
SDL_Rect cyanBrick = {64, 0, 32, 16};
SDL_Rect lightGreenBrick = {96, 0, 32, 16};
SDL_Rect darkBlueBrick = {128, 0, 32, 16};
SDL_Rect darkGreenBrick = {160, 0, 32, 16};
SDL_Rect lightRedBrick = {0, 16, 32, 16};
SDL_Rect blueBrick = {32, 16, 32, 16};
SDL_Rect pinkBrick = {64, 16, 32, 16};
SDL_Rect yellowBrick = {96, 16, 32, 16};
SDL_Rect darkRedBrick = {128, 16, 32, 16};
SDL_Rect darkCyanBrick = {160, 16, 32, 16};
SDL_Rect defaultBrick = {0, 0, 0, 0};

SDL_Rect get_brick_src_rect(int brick_number) {
    SDL_Rect srcRect;
    switch (brick_number) {
        case 1:
            srcRect = whiteBrick; // Brique blanche
            brick_points = 60;
            break;
        case 2:
            srcRect = orangeBrick; // Brique orange
            brick_points = 65;
            break;
        case 3:
            srcRect = cyanBrick; // Brique cyan clair
            brick_points = 70;
            break;
        case 4:
            srcRect = lightGreenBrick; // Brique vert clair
            brick_points = 75;
            break;
        case 5:
            srcRect = darkBlueBrick; // Brique bleu foncé
            brick_points = 80;
            break;
        case 6:
            srcRect = darkGreenBrick; // Brique vert foncé
            brick_points = 85;
            break;
        case 7:
            srcRect = lightRedBrick; // Brique rouge clair
            brick_points = 90;
            break;
        case 8:
            srcRect = blueBrick; // Brique bleu
            brick_points = 95;
            break;
        case 9:
            srcRect = pinkBrick; // Brique rose
            brick_points = 100;
            break;
        case 10:
            srcRect = yellowBrick; // Brique jaune
            brick_points = 105;
            break;
        case 11:
            srcRect = darkRedBrick; // Brique rouge foncé
            brick_points = 110;
            break;
        case 12:
            srcRect = darkCyanBrick; // Brique cyan foncé
            brick_points = 115;
            break;
        case 20:
            srcRect = silverBrickStates[0]; // Brique argent
            brick_points = 200;
            break;
        case 30:
            srcRect = goldenBrickStates[0]; // Brique or
            break;
        default:
            srcRect = defaultBrick; // Brique par défaut
            break;
    }
    return srcRect;
}

void load_level(const char *filename, brick bricks[], int *brick_count) {
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
                brick_health = -1;
            }

            if (srcRect.w > 0 && srcRect.h > 0) {
                brick *brick = &bricks[*brick_count];
                create_brick(brick, x * BRICK_WIDTH, y * BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT, brick_health, brick_points);
                brick->srcRect = srcRect; // Définit le rectangle source basé sur le numéro
                if (brick_number == 30) {
                    brick->isGold = 1;
                } else if (brick_number == 20) {
                    brick->isSilver = 1;
                }
                else{
                    brick->isGold = 0;
                    brick->isSilver = 0;
                }
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

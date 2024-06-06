//
// Created by OfferleA on 5/28/2024.
//

#include "graphics.h"
#include "constant.h"

SDL_Rect srcBg = {0, 128, 96, 128}; // x,y, w,h (0,0) en haut a gauche
SDL_Rect srcBall = {0, 96, 24, 24};
SDL_Rect srcVaiss = {128, 0, 128, 32};
SDL_Rect srcBrick = {0, 0, 32, 16};

SDL_Surface *textSprite;


SDL_Rect backgrounds[12] = {
        {0, 128, 48, 64}, //default
        {0, 192, 48, 64}, //default dark
        {64, 128, 64, 64}, //blue
        {64, 192, 64, 64}, //blue dark
        {128, 128, 64, 64}, //green
        {128, 192, 64, 64}, //green dark
        {256, 128, 64, 64}, //red
        {256, 192, 64, 64}, //red dark
        {320, 128, 64, 64}, //orange
        {320, 192, 64, 64}, //orange dark
        {384, 128, 64, 64}, //purple
        {384, 192, 64, 64} //purple dark
};


SDL_Rect _0 = {0, 32, 32, 32};
SDL_Rect _1 = {32, 32, 32, 32};
SDL_Rect _2 = {64, 32, 32, 32};
SDL_Rect _3 = {96, 32, 32, 32};
SDL_Rect _4 = {128, 32, 32, 32};
SDL_Rect _5 = {160, 32, 32, 32};
SDL_Rect _6 = {192, 32, 32, 32};
SDL_Rect _7 = {224, 32, 32, 32};
SDL_Rect _8 = {256, 32, 32, 32};
SDL_Rect _9 = {288, 32, 32, 32};

// Définitions des lettres avec positions et dimensions spécifiées
SDL_Rect A = {32, 64, 32, 32};
SDL_Rect B = {64, 64, 32, 32};
SDL_Rect C = {96, 64, 32, 32};
SDL_Rect D = {128, 64, 32, 32};
SDL_Rect E = {160, 64, 32, 32};
SDL_Rect F = {192, 64, 32, 32};
SDL_Rect G = {224, 64, 32, 32};
SDL_Rect H = {256, 64, 32, 32};
SDL_Rect I = {288, 64, 32, 32};
SDL_Rect J = {320, 64, 32, 32};
SDL_Rect K = {352, 64, 32, 32};
SDL_Rect L = {384, 64, 32, 32};
SDL_Rect M = {416, 64, 32, 32};
SDL_Rect N = {448, 64, 32, 32};
SDL_Rect O = {480, 64, 32, 32};
SDL_Rect P = {0, 96, 32, 32};
SDL_Rect Q = {32, 96, 32, 32};
SDL_Rect R = {64, 96, 32, 32};
SDL_Rect S = {96, 96, 32, 32};
SDL_Rect T = {128, 96, 32, 32};
SDL_Rect U = {160, 96, 32, 32};
SDL_Rect V = {192, 96, 32, 32};
SDL_Rect W = {224, 96, 32, 32};
SDL_Rect X = {256, 96, 32, 32};
SDL_Rect Y = {288, 96, 32, 32};
SDL_Rect Z = {320, 96, 32, 32};

SDL_Surface *load_image(const char *path)
{
    SDL_Surface *optimizedImage = NULL;
    SDL_Surface *loadedImage = SDL_LoadBMP(path);
    if (loadedImage != NULL)
    {
        optimizedImage = SDL_ConvertSurface(loadedImage, window_surface->format, 0);
        SDL_FreeSurface(loadedImage);
    }
    else{
        perror("Error while loading the sprites");
    }
    return optimizedImage;
}

SDL_Surface* init_window()
{
    window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        perror("Error while creating the window");
        exit(1);
    }
    window_surface = SDL_GetWindowSurface(window);
    if (window_surface == NULL)
    {
        perror("Error while getting the window's surface");
        exit(1);
    }
    plancheSprites = load_image("sprites.bmp");
    if (plancheSprites == NULL)
    {
        perror("Error while loading the sprites");
        exit(1);
    }
    brickSprite = load_image("Arkanoid_sprites.bmp");
    if (brickSprite == NULL)
    {
        perror("Error while loading the brick sprite");
        exit(1);
    }
    textSprite = load_image("Arkanoid_ascii.bmp");
    if (textSprite == NULL)
    {
        perror("Error while loading the text sprite");
        exit(1);
    }
    SDL_SetColorKey(plancheSprites, 1, 0); // 0: 00/00/00 noir -> transparent
    return SDL_GetWindowSurface(window);
}

void draw_ball(ball *b) {
    SDL_BlitSurface(plancheSprites, &srcBall, window_surface, &(SDL_Rect){b->x, b->y, 0, 0});
}

void draw_paddle(paddle *p) {
    SDL_Rect rect = {p->x, p->y, p->w, p->h};
    SDL_BlitSurface(plancheSprites, &srcVaiss, window_surface, &rect);
}

void draw_brick(brick *b) {
    SDL_Rect rect = get_brick_rect(b);
    SDL_BlitSurface(brickSprite, &rect, window_surface, &(SDL_Rect){b->x, b->y, b->w, b->h});
}

void draw_bricks(brick *b, int n) {
    for (int i = 0; i < n; i++) {
        if (!is_brick_dead(&b[i])) {
            draw_brick(&b[i]);
        }
    }
}

void blit_background() {
    const int bg_width = backgrounds[background].w;
    const int bg_height = backgrounds[background].h;
    const int window_width = PLAYABLE_ZONE_WIDTH;
    const int window_height = window_surface->h;
    SDL_Rect tube = {192, 0, 8, 23};

    // Check if the window's width and height are multiples of the background image's width and height
    if (window_width % bg_width == 0 && window_height % bg_height == 0) {
        for (int j = 0; j < window_height; j += bg_height)
            for (int i = 0; i < window_width; i += bg_width)
            {
                dest.x = i;
                dest.y = j;
                if (SDL_BlitSurface(brickSprite, &backgrounds[background], window_surface, &dest) != 0)
                {
                    perror("Error while blitting the background");
                    exit(1);
                }
            }
    } else {
        // If not, fall back to the original method
        for (int j = 0; j < window_height; j += bg_height)
            for (int i = 0; i < window_width; i += bg_width)
            {
                dest.x = i;
                dest.y = j;
                if (SDL_BlitSurface(brickSprite, &backgrounds[background], window_surface, &dest) != 0)
                {
                    perror("Error while blitting the background");
                    exit(1);
                }
            }
    }
    SDL_Rect blackRect = {416, 0, SCREEN_WIDTH, SCREEN_HEIGHT};  // x, y, width, height

    // Dessiner un rectangle noir
    SDL_FillRect(window_surface, &blackRect, SDL_MapRGB(window_surface->format, 0, 0, 0));
}

void update_window() {
    SDL_UpdateWindowSurface(window);
}

void draw_powerup(PowerUp *p) {
    SDL_Rect dest = {p->x, p->y, p->w, p->h};
    SDL_FillRect(window_surface, &dest, SDL_MapRGB(window_surface->format, 255,255,p->type * (255/2)));
}

void draw_powerups(PowerUp *p, int n) {
    for (int i = 0; i < n; i++) {
        if (p[i].active) {
            draw_powerup(&p[i]);
        }
    }
}

void write_score(int score){
    SDL_Rect destRect;
    destRect.x = 500;
    destRect.y = 50;
    destRect.w = 32;
    destRect.h = 32;

    SDL_BlitSurface(textSprite, &S, window_surface, &destRect);
    destRect.x += 20;
    SDL_BlitSurface(textSprite, &C, window_surface, &destRect);
    destRect.x += 20;
    SDL_BlitSurface(textSprite, &O, window_surface, &destRect);
    destRect.x += 20;
    SDL_BlitSurface(textSprite, &R, window_surface, &destRect);
    destRect.x += 20;
    SDL_BlitSurface(textSprite, &E, window_surface, &destRect);

    // Convertir le score en chaîne de caractères
    char scoreStr[10];
    sprintf(scoreStr, "%d", score);

    // Position initiale pour blit
    int posX = 500;

    // Pour chaque caractère dans la chaîne de score
    for (int i = 0; scoreStr[i] != '\0'; ++i) {
        SDL_Rect srcRect;
        // Sélectionner le rectangle source correspondant au chiffre
        switch (scoreStr[i]) {
            case '0': srcRect = _0; break;
            case '1': srcRect = _1; break;
            case '2': srcRect = _2; break;
            case '3': srcRect = _3; break;
            case '4': srcRect = _4; break;
            case '5': srcRect = _5; break;
            case '6': srcRect = _6; break;
            case '7': srcRect = _7; break;
            case '8': srcRect = _8; break;
            case '9': srcRect = _9; break;
        }

        // Définir le rectangle de destination
        SDL_Rect destRectScore = {posX, 100, 32, 32};

        // Blit le chiffre sur la surface de l'écran
        SDL_BlitSurface(textSprite, &srcRect, window_surface, &destRectScore);

        // Avancer la position en x pour le prochain chiffre
        posX += 20;
    }
}
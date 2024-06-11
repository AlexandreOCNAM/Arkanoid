//
// Created by OfferleA on 5/28/2024.
//

#include "graphics.h"
#include "constant.h"

SDL_Surface *textSprite;

int background = 0;

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
    brickSprite = load_image("../public/Arkanoid_sprites.bmp");
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
    SDL_SetColorKey(brickSprite, 1, 0); // 0: 00/00/00 noir -> transparent
    return SDL_GetWindowSurface(window);
}


void draw_balls(ball **b, int count) {
    for (int i = 0; i < count; i++) {
        if (b[i]->active == 1) {
            draw_ball(b[i]);
        }
    }
}

void draw_ball(ball *b) {
    if (b == NULL) {
        return;
    }
    SDL_BlitSurface(brickSprite, &srcBall, window_surface, &(SDL_Rect){b->x, b->y, 0, 0});
}

void draw_paddle(paddle *p) {
    SDL_BlitSurface(brickSprite, &p->srcRect, window_surface, &(SDL_Rect){p->x, p->y, 0, 0});
}

void draw_brick(brick *b) {
    SDL_Rect rect = get_brick_rect(b);
    SDL_BlitSurface(brickSprite, &rect, window_surface, &(SDL_Rect){b->x, b->y, b->w+1, b->h+1});
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
    const int window_height =  PLAYABLE_ZONE_HEIGHT;
    SDL_Rect black = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};  // x, y, width, height
    SDL_FillRect(window_surface, &black, SDL_MapRGB(window_surface->format, 0, 0, 0));

    for (int j = PLAYABLE_ZONE_HEIGHT_START; j < window_height; j += bg_height)
        for (int i = PLAYABLE_ZONE_WIDTH_START; i < window_width; i += bg_width)
        {
            dest.x = i;
            dest.y = j;
            if (SDL_BlitSurface(brickSprite, &backgrounds[background], window_surface, &dest) != 0)
            {
                perror("Error while blitting the background");
                exit(1);
            }
        }

    SDL_Rect blackRect = {PLAYABLE_ZONE_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT};  // x, y, width, height
    SDL_FillRect(window_surface, &blackRect, SDL_MapRGB(window_surface->format, 0, 0, 0));
    draw_outer();
}

void draw_outer(){
    dest.x = 0;
    dest.y = 0;
    SDL_BlitSurface(brickSprite, &corner_top_left, window_surface, &dest);
    dest.x = 0;
    dest.y = PLAYABLE_ZONE_HEIGHT;
    SDL_BlitSurface(brickSprite, &corner_bottom_left, window_surface, &dest);
    dest.x = PLAYABLE_ZONE_WIDTH;
    dest.y = 0;
    SDL_BlitSurface(brickSprite, &corner_top_right, window_surface, &dest);
    dest.x = PLAYABLE_ZONE_WIDTH;
    dest.y = PLAYABLE_ZONE_HEIGHT;
    SDL_BlitSurface(brickSprite, &corner_bottom_right, window_surface, &dest);
    for(int y = PLAYABLE_ZONE_HEIGHT_START; y < PLAYABLE_ZONE_HEIGHT; y += 48+32){
        dest.x = 0;
        dest.y = y;
        SDL_BlitSurface(brickSprite, &big_tube_v, window_surface, &dest);
        dest.x = PLAYABLE_ZONE_WIDTH;
        SDL_BlitSurface(brickSprite, &big_tube_v, window_surface, &dest);

        dest.x = 0;
        dest.y = y+48;
        if(dest.y < PLAYABLE_ZONE_HEIGHT) {
            SDL_BlitSurface(brickSprite, &tube_v, window_surface, &dest);
            dest.x = PLAYABLE_ZONE_WIDTH;
            SDL_BlitSurface(brickSprite, &tube_v, window_surface, &dest);
        }
    }
    for(int x = PLAYABLE_ZONE_WIDTH_START; x < PLAYABLE_ZONE_WIDTH; x += 32){
        dest.x = x;
        dest.y = 0;

        if(x == PLAYABLE_ZONE_WIDTH_START+64 || x == PLAYABLE_ZONE_WIDTH_START+32*7+48) {
            SDL_BlitSurface(brickSprite, &big_tube_h, window_surface, &dest);
            x += 16;
        }
        else{
            SDL_BlitSurface(brickSprite, &tube_h, window_surface, &dest);
        }
    }
}

void update_window() {
    SDL_UpdateWindowSurface(window);
}

void draw_powerup(PowerUp *pu) {
    SDL_Rect dest = {pu->x, pu->y, pu->w, pu->h};
    SDL_BlitSurface(brickSprite, &pu->srcRect, window_surface, &dest);
}

void draw_powerups(PowerUp *p, int n) {
    for (int i = 0; i < n; i++) {
        if (p[i].active == 1) {
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

    char scoreStr[10];
    sprintf(scoreStr, "%d", score);

    int posX = 500;

    for (int i = 0; scoreStr[i] != '\0'; ++i) {
        SDL_Rect srcRect;
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

        SDL_Rect destRectScore = {posX, 100, 32, 32};

        SDL_BlitSurface(textSprite, &srcRect, window_surface, &destRectScore);

        posX += 20;
    }
}

void write_lives(int lives){
    SDL_Rect destRect;
    destRect.x = 500;
    destRect.y = 150;
    destRect.w = 32;
    destRect.h = 32;

    SDL_BlitSurface(textSprite, &L, window_surface, &destRect);
    destRect.x += 20;
    SDL_BlitSurface(textSprite, &I, window_surface, &destRect);
    destRect.x += 20;
    SDL_BlitSurface(textSprite, &V, window_surface, &destRect);
    destRect.x += 20;
    SDL_BlitSurface(textSprite, &E, window_surface, &destRect);
    destRect.x += 20;
    SDL_BlitSurface(textSprite, &S, window_surface, &destRect);

    // Convertir le score en chaîne de caractères
    char livesStr[10];
    sprintf(livesStr, "%d", lives);

    // Position initiale pour blit
    int posX = 500;

    // Pour chaque caractère dans la chaîne de score
    for (int i = 0; livesStr[i] != '\0'; ++i) {
        SDL_Rect srcRect;
        // Sélectionner le rectangle source correspondant au chiffre
        switch (livesStr[i]) {
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
        SDL_Rect destRectScore = {posX, 200, 32, 32};

        // Blit le chiffre sur la surface de l'écran
        SDL_BlitSurface(textSprite, &srcRect, window_surface, &destRectScore);

        // Avancer la position en x pour le prochain chiffre
        posX += 20;
    }
}

void draw_lasers(laser *l, int n) {
    for (int i = 0; i < n; i++) {
        if (l[i].active == 1)
            draw_laser(&l[i]);
    }
}

void draw_laser(laser *l) {
    // blit a red rectangle
    SDL_FillRect(window_surface, &(SDL_Rect){l->x, l->y, l->w, l->h}, SDL_MapRGB(window_surface->format, 255, 0, 0));
}

void draw_droid(droid *d) {
    SDL_BlitSurface(brickSprite, &d->srcRect, window_surface, &(SDL_Rect){d->x, d->y, 0, 0});
}

void draw_droids(droid *d, int n) {
    for (int i = 0; i < n; i++) {
        if (d[i].active == 1) {
            draw_droid(&d[i]);
        }
    }
}
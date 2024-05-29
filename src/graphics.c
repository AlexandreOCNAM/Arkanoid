//
// Created by OfferleA on 5/28/2024.
//

#include "graphics.h"

SDL_Window *window = NULL;
SDL_Surface *window_surface = NULL;
SDL_Surface *plancheSprites = NULL;
SDL_Surface *brickSprite = NULL;

SDL_Rect srcBg = {0, 128, 96, 128}; // x,y, w,h (0,0) en haut a gauche
SDL_Rect srcBall = {0, 96, 24, 24};
SDL_Rect srcVaiss = {128, 0, 128, 32};
SDL_Rect srcBrick = {0, 0, 190, 62};

SDL_Surface *load_image(const char *path)
{
    SDL_Surface *optimizedImage = NULL;
    SDL_Surface *loadedImage = SDL_LoadBMP(path);
    if (loadedImage != NULL)
    {
        optimizedImage = SDL_ConvertSurface(loadedImage, window_surface->format, 0);
        SDL_FreeSurface(loadedImage);
    }
    return optimizedImage;
}

SDL_Surface* init_window()
{
    window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
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
    plancheSprites = load_image("./sprites.bmp");
    if (plancheSprites == NULL)
    {
        perror("Error while loading the sprites");
        exit(1);
    }
    brickSprite = load_image("./Arkanoid_sprites.bmp");
    if (brickSprite == NULL)
    {
        perror("Error while loading the brick sprite");
        exit(1);
    }
    SDL_SetColorKey(plancheSprites, 1, 0); // 0: 00/00/00 noir -> transparent
    return SDL_GetWindowSurface(window);
}

void draw_ball(ball *b) {
    SDL_BlitSurface(plancheSprites, &srcBall, window_surface, &(SDL_Rect){b->x, b->y, 0, 0});
}

void draw_paddle(paddle *p) {
    SDL_Rect dest = {p->x, p->y, p->w, p->h};
    SDL_BlitSurface(plancheSprites, &srcVaiss, window_surface, &dest);
}

void draw_brick(brick *b) {
    SDL_Rect dest = {b->x, b->y, 0, 0};
    // print the brick with random color
    SDL_FillRect(window_surface, &dest, SDL_MapRGB(window_surface->format, rand() % 255, rand() % 255, rand() % 255));
}

void draw_bricks(brick *b, int n) {
    for (int i = 0; i < n; i++) {
        if (b[i].health > 0) {
            draw_brick(&b[i]);
        }
    }
}

void blit_background(SDL_Rect *dest) {
    const int bg_width = srcBg.w;
    const int bg_height = srcBg.h;
    const int window_width = window_surface->w;
    const int window_height = window_surface->h;

    // Check if the window's width and height are multiples of the background image's width and height
    if (window_width % bg_width == 0 && window_height % bg_height == 0) {
        for (int j = 0; j < window_height; j += bg_height)
            for (int i = 0; i < window_width; i += bg_width)
            {
                dest->x = i;
                dest->y = j;
                if (SDL_BlitSurface(plancheSprites, &srcBg, window_surface, dest) != 0)
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
                dest->x = i;
                dest->y = j;
                if (SDL_BlitSurface(plancheSprites, &srcBg, window_surface, dest) != 0)
                {
                    perror("Error while blitting the background");
                    exit(1);
                }
            }
    }

}

void update_window() {
    SDL_UpdateWindowSurface(window);
}

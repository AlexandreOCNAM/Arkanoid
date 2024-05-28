//
// Created by alexa on 3/7/2024.
//

#ifndef ARKANOID_WINDOW_H
#define ARKANOID_WINDOW_H

#include "./includes.h"

SDL_Window *window = NULL;
SDL_Surface *window_surface = NULL;
SDL_Surface *plancheSprites = NULL;

SDL_Rect srcBg = {0, 128, 96, 128}; // x,y, w,h (0,0) en haut a gauche
SDL_Rect srcBall = {0, 96, 24, 24};
SDL_Rect srcVaiss = {128, 0, 128, 32};
SDL_Rect srcBrick = {0, 0, 32, 16};




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

void init_window()
{
    window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, SDL_WINDOW_SHOWN);
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
    SDL_SetColorKey(plancheSprites, true, 0); // 0: 00/00/00 noir -> transparent
}

void destroy_window()
{
  SDL_DestroyWindow(window);
}

void blit_background(SDL_Rect *dest){
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

void draw_ball(ball* b)
{
    if (window == NULL || window_surface == NULL || plancheSprites == NULL)
    {
        perror("Error while drawing the ball: window, window_surface or plancheSprites is NULL");
        exit(1);
    }
    else
    {
        SDL_Rect dstBall = {b->rect.x, b->rect.y, 0, 0};
        SDL_BlitSurface(plancheSprites, &srcBall, window_surface, &dstBall);
    }
}


#endif //ARKANOID_WINDOW_H

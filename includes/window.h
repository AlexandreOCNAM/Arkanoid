//
// Created by alexa on 3/7/2024.
//

#ifndef ARKANOID_WINDOW_H
#define ARKANOID_WINDOW_H

#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Window *window = NULL;
SDL_Surface *window_surface = NULL;
SDL_Surface *plancheSprites = NULL;

SDL_Rect srcBg = {0, 128, 96, 128}; // x,y, w,h (0,0) en haut a gauche
SDL_Rect srcBall = {0, 96, 24, 24};
SDL_Rect srcVaiss = {128, 0, 128, 32};
void init_window()
{
  window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
  window_surface = SDL_GetWindowSurface(window);
  plancheSprites = SDL_LoadBMP("./sprites.bmp");
  SDL_SetColorKey(plancheSprites, true, 0); // 0: 00/00/00 noir -> transparent
}

void destroy_window()
{
  SDL_DestroyWindow(window);
}

int blit_background(SDL_Rect *dest){
  for (int j = 0; j < window_surface->h; j += 128)
    for (int i = 0; i < window_surface->w; i += 96)
    {
      dest->x = i;
      dest->y = j;
      SDL_BlitSurface(plancheSprites, &srcBg, window_surface, dest);
    }
}


#endif //ARKANOID_WINDOW_H

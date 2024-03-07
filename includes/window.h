//
// Created by alexa on 3/7/2024.
//

#ifndef ARKANOID_WINDOW_H
#define ARKANOID_WINDOW_H

#include <SDL2/SDL.h>

SDL_Window *window = NULL;
SDL_Surface *window_surface = NULL;

void init_window()
{
  window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
  window_surface = SDL_GetWindowSurface(window);
}

void destroy_window()
{
  SDL_DestroyWindow(window);
}



#endif //ARKANOID_WINDOW_H

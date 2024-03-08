#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../includes/ball.h"
#include "includes/window.h"
#include "includes/paddle.h"

const int FPS = 60.0;
// struct { double x; double y; } ball_speed;
//struct
//{
//  double x;
//  double y;
//  double vx;
//  double vy;
//} ball;

ball _ball = {0};

Uint64 prev, now; // timers
double delta_t;   // durée frame en ms
int x_vault;


//SDL_Rect srcBg = {0, 128, 96, 128}; // x,y, w,h (0,0) en haut a gauche
//SDL_Rect srcBall = {0, 96, 24, 24};
//SDL_Rect srcVaiss = {128, 0, 128, 32};

void init()
{
//  pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
//  win_surf = SDL_GetWindowSurface(pWindow);
//  plancheSprites = SDL_LoadBMP("./sprites.bmp");
//  SDL_SetColorKey(plancheSprites, true, 0); // 0: 00/00/00 noir -> transparent

  init_window();

  _ball = (ball){
          window_surface->w / 2,
          window_surface->h / 2,
          {
              1.0,
              1.4
          }
  };
//  ball.x = win_surf->w / 2;
//  ball.y = win_surf->h / 2;
//  ball.v.x = 1.0;
//  ball.v.y = 1.4;
//
  now = SDL_GetPerformanceCounter();
}

void draw()
{
  // remplit le fond
  SDL_Rect dest = {0, 0, 0, 0};
  blit_background(&dest);

  // affiche balle
//  SDL_Rect dstBall = {_ball.x, _ball.y, 0, 0};
//  SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);
  draw_ball(window_surface, plancheSprites, srcBall, _ball);

  // deplacement

  move_ball(&_ball);

  // collision avec les murs
//  collision_type c = ball_collide_wall(&_ball, window_surface->w, window_surface->h);
//  if (c == HORZ)
//    invert_x_speed(&_ball);
//  if (c == VERT)
//    invert_y_speed(&_ball);

  ball_collide_walls(&_ball, &window_surface->clip_rect);
// touche bas -> rouge

  // collision of ball with the paddle
  // if ((ball.x > x_vault) && (ball.x < (x_vault + 128)) && (ball.y > (win_surf->h - 32 -24)))
//  if (collision(_ball.x, _ball.y, 24, 24, x_vault, win_surf->h - 32, 128, 32))
//    invert_y_speed(&_ball);



  // vaisseau
  dest.x = x_vault;
  dest.y = window_surface->h - 32;
  SDL_BlitSurface(plancheSprites, &srcVaiss, window_surface, &dest);
//  ball_collide_rect(&_ball, &dest);
  paddle_collide_ball(&dest, &_ball);

}

int main(int argc, char **argv)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
  {
    perror("Error while initializing SDL");
    return 1;
  }

  init();

  SDL_Rect test = {50, 50, 50, 50};
  int x = 55;
  int y = 45;
  int x1 = 55;
  int y1 = 105;

  SDL_IntersectRectAndLine(&test, &x, &y, &x1, &y1);
  printf("x = %d, y = %d, x1 = %d, y1 = %d\n", x, y, x1, y1);

  bool quit = false;
  while (!quit)
  {
    SDL_PumpEvents();
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT])
      // collision of the paddle with the left wall
      if (x_vault > 0)
        x_vault -= 10;
    if (keys[SDL_SCANCODE_RIGHT])
      // collision of the paddle with the right wall
      if (x_vault < (window_surface->w - 128 - 10))
        x_vault += 10;
    if (keys[SDL_SCANCODE_ESCAPE])
      quit = true;

    draw();
    SDL_UpdateWindowSurface(window);
    now = SDL_GetPerformanceCounter();
    delta_t = 1.0 / FPS - (double)(now - prev) / (double)SDL_GetPerformanceFrequency();
    prev = now;
    if (delta_t > 0)
      SDL_Delay((Uint32)(delta_t * 1000));
    // printf("dt = %lf\n",delta_t*1000);
    prev = SDL_GetPerformanceCounter();
  }

  SDL_Quit();
  return 0;
}

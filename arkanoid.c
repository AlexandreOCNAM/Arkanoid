#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../includes/ball.h"

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

SDL_Window *pWindow = NULL;
SDL_Surface *win_surf = NULL;
SDL_Surface *plancheSprites = NULL;

SDL_Rect srcBg = {0, 128, 96, 128}; // x,y, w,h (0,0) en haut a gauche
SDL_Rect srcBall = {0, 96, 24, 24};
SDL_Rect srcVaiss = {128, 0, 128, 32};

void init()
{
  pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
  win_surf = SDL_GetWindowSurface(pWindow);
  plancheSprites = SDL_LoadBMP("./sprites.bmp");
  SDL_SetColorKey(plancheSprites, true, 0); // 0: 00/00/00 noir -> transparent

  _ball = (ball){
          win_surf->w / 2,
          win_surf->h / 2,
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

int collision(int x, int y, int w, int h, int x2, int y2, int w2, int h2)
{
  if (x + w < x2)
    return 0;
  if (x > x2 + w2)
    return 0;
  if (y + h < y2)
    return 0;
  if (y > y2 + h2)
    return 0;
  return 1;
}

void draw()
{
  // remplit le fond
  SDL_Rect dest = {0, 0, 0, 0};
  for (int j = 0; j < win_surf->h; j += 128)
    for (int i = 0; i < win_surf->w; i += 96)
    {
      dest.x = i;
      dest.y = j;
      SDL_BlitSurface(plancheSprites, &srcBg, win_surf, &dest);
    }

  // affiche balle
//  SDL_Rect dstBall = {_ball.x, _ball.y, 0, 0};
//  SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);
  draw_ball(win_surf, plancheSprites, srcBall, _ball);

  // deplacement

  move_ball(&_ball);

  // collision avec les murs
  collision_type c = ball_collide_wall(&_ball, win_surf->w, win_surf->h);
  if (c == HORZ)
    invert_x_speed(&_ball);
  if (c == VERT)
    invert_y_speed(&_ball);

  // touche bas -> rouge
  if (_ball.y > (win_surf->h - 25))
    srcBall.y = 64;
  // touche bas -> vert
  if (_ball.y < 1)
    srcBall.y = 96;

  // collision of ball with the paddle
  // if ((ball.x > x_vault) && (ball.x < (x_vault + 128)) && (ball.y > (win_surf->h - 32 -24)))
//  if (collision(_ball.x, _ball.y, 24, 24, x_vault, win_surf->h - 32, 128, 32))
//    invert_y_speed(&_ball);



  // vaisseau
  dest.x = x_vault;
  dest.y = win_surf->h - 32;
  SDL_BlitSurface(plancheSprites, &srcVaiss, win_surf, &dest);

  collision_type br = ball_collide_rect(&_ball, &dest);
  if (br == VERT)
    invert_x_speed(&_ball);
  if (br == HORZ)
    invert_y_speed(&_ball);
  if (br == BOTH)
  {
    invert_x_speed(&_ball);
    invert_y_speed(&_ball);
  }
}

int main(int argc, char **argv)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
  {
    perror("Error while initializing SDL");
    return 1;
  }

  init();

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
      if (x_vault < (win_surf->w - 128 - 10))
        x_vault += 10;
    if (keys[SDL_SCANCODE_ESCAPE])
      quit = true;

    draw();
    SDL_UpdateWindowSurface(pWindow);
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

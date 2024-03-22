#include "includes/includes.h"

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

SDL_Surface *brickSprite = NULL;


Uint64 prev, now; // timers
double delta_t;   // durée frame en ms
int x_vault;

SDL_Rect dest = {0, 0, 0, 0};
SDL_Rect tmp = {0, 0, 0, 0};

paddle _paddle = {0};
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

  // _ball = (ball){
  //         window_surface->w / 2,
  //         window_surface->h / 2,
  //             1.0,
  //             1.4
  //         }
  // };
  _ball = create_ball();
//  ball.x = win_surf->w / 2;
//  ball.y = win_surf->h / 2;
//  ball.v.x = 1.0;
//  ball.v.y = 1.4;
//
  now = SDL_GetPerformanceCounter();


  // init the sprites of the bricks
  brickSprite = load_image("./Arkanoid_sprites.bmp");
  if (brickSprite == NULL)
  {
    perror("Error while loading the brick sprite");
    exit(1);
  }
  SDL_SetColorKey(brickSprite, true, 0); // 0: 00/00/00 noir -> transparent

  SDL_BlitSurface(brickSprite, &srcBrick, window_surface, &tmp);
  _paddle = create_paddle();
}

void draw()
{
  // remplit le fond
  blit_background(&dest);

  // affiche balle
//  SDL_Rect dstBall = {_ball.x, _ball.y, 0, 0};
//  SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);
  draw_ball(&_ball);
  // deplacement


  // collision avec les murs
//  collision_type c = ball_collide_wall(&_ball, window_surface->w, window_surface->h);
//  if (c == HORZ)
//    invert_x_speed(&_ball);
//  if (c == VERT)
//    invert_y_speed(&_ball);

// touche bas -> rouge

  // collision of ball with the paddle
  // if ((ball.x > x_vault) && (ball.x < (x_vault + 128)) && (ball.y > (win_surf->h - 32 -24)))
//  if (collision(_ball.x, _ball.y, 24, 24, x_vault, win_surf->h - 32, 128, 32))
//    invert_y_speed(&_ball);



  // vaisseau
  dest.x = x_vault;
  dest.y = window_surface->h - 16;
  SDL_BlitSurface(plancheSprites, &srcVaiss, window_surface, &_paddle.rect);
//  ball_collide_rect(&_ball, &dest);

  SDL_BlitSurface(brickSprite, &srcBrick, window_surface, &tmp);

}

int main(int argc, char **argv)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
  {
    perror("Error while initializing SDL");
    return 1;
  }

  init();

  SDL_Rect test = {100, 100, 100, 100};

  bool quit = false;
  while (!quit)
  {
    SDL_PumpEvents();
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT])
      // collision of the paddle with the left wall
        strafe_left(&_paddle);
    if (keys[SDL_SCANCODE_RIGHT])
      // collision of the paddle with the right wall
        strafe_right(&_paddle);
    if (keys[SDL_SCANCODE_ESCAPE])
      quit = true;

    move_ball(&_ball);
    printf("move ball\n");
    paddle_collide_walls(&_paddle, window_surface->w);
    printf("paddle collide walls\n");
    ball_collide_walls(&_ball, &window_surface->clip_rect);
    ball_collide_rect(&_ball, &test);
    ball_collide_rect(&_ball, &_paddle.rect);
    draw();
    // fill test rect with white
    SDL_FillRect(window_surface, &test, SDL_MapRGB(window_surface->format, 255, 255, 255));
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

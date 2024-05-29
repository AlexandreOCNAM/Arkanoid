
#include "src/ball.h"
#include "src/brick.h"
#include "src/paddle.h"
#include "src/graphics.h"
#include "src/collisions.h"
#include "src/extractFile.h"

const int FPS = 60.0;

ball _ball = {0};
SDL_Surface *BrickSprite = NULL;

SDL_Window *window = NULL;
SDL_Surface *window_surface = NULL;
SDL_Surface *plancheSprites = NULL;
SDL_Surface *brickSprite = NULL;

Uint64 prev, now; // timers
double delta_t;   // durée frame en ms
int x_vault;

SDL_Rect dest = {0, 0, 100, 100};


paddle _paddle = {0};
//SDL_Rect srcBg = {0, 128, 96, 128}; // x,y, w,h (0,0) en haut a gauche
//SDL_Rect srcBall = {0, 96, 24, 24};
//SDL_Rect srcVaiss = {128, 0, 128, 32};

SDL_Surface *win_surf = NULL;
Brick bricks[100];
int brick_count = 0;

void init()
{


//  pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
//  win_surf = SDL_GetWindowSurface(pWindow);
//  plancheSprites = SDL_LoadBMP("./sprites.bmp");
//  SDL_SetColorKey(plancheSprites, true, 0); // 0: 00/00/00 noir -> transparent
  win_surf = init_window();

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
  BrickSprite = load_image("./Arkanoid_sprites.bmp");
  if (BrickSprite == NULL)
  {
    perror("Error while loading the brick sprite");
    exit(1);
  }
  SDL_SetColorKey(BrickSprite, true, 0); // 0: 00/00/00 noir -> transparent

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
    draw_paddle(&_paddle);

    draw_bricks(bricks, brick_count);
    update_window();
}

int main(int argc, char **argv)
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        perror("Error while initializing SDL");
        return 1;
    }

    init();

    // Charger les niveaux
    load_level("../Levels/niveau4.txt", bricks, &brick_count);

  bool quit = false;
  while (!quit)
  {
      SDL_PumpEvents();
      const Uint8 *keys = SDL_GetKeyboardState(NULL);
      if (keys[SDL_SCANCODE_LEFT]) {
          // collision of the paddle with the left wall
          strafe_paddle(&_paddle, 0);
      }
      else if (keys[SDL_SCANCODE_RIGHT]){
          // collision of the paddle with the right wall
          strafe_paddle(&_paddle, 1);
      }
      else
          _paddle.vx = 0;
      if (keys[SDL_SCANCODE_ESCAPE])
          quit = true;
      move_ball(&_ball, &win_surf->clip_rect, &_paddle, bricks, 1);
    draw();

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

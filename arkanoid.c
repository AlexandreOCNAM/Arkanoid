#include "includes/includes.h"
#include "../includes/ball.h"
#include "../includes/extractFile.h" // Assurez-vous que ce fichier est inclus
#include "includes/window.h"
#include "includes/paddle.h"
#include "includes/brick.h"

const int FPS = 60.0;

ball _ball = {0};
SDL_Surface *brickSprite = NULL;

Uint64 prev, now; // timers
double delta_t;   // durée frame en ms
int x_vault;

SDL_Rect dest = {0, 0, 0, 0};


paddle _paddle = {0};

Brick bricks[100];
int brick_count = 0;

void init()
{
    init_window();
    _ball = create_ball();
    now = SDL_GetPerformanceCounter();

    // init the sprites of the bricks
    brickSprite = load_image("./Arkanoid_sprites.bmp");
    if (brickSprite == NULL)
    {
        perror("Error while loading the brick sprite");
        exit(1);
    }
    SDL_SetColorKey(brickSprite, true, 0); // 0: 00/00/00 noir -> transparent

    _paddle = create_paddle();
}

void draw()
{
    // remplit le fond
    blit_background(&dest);
    // affiche balle
    draw_ball(&_ball);
    // vaisseau
    dest.x = x_vault;
    dest.y = window_surface->h - 16;
    SDL_BlitSurface(plancheSprites, &srcVaiss, window_surface, &_paddle.rect);

    // Dessiner les briques
    for (int i = 0; i < brick_count; i++)
    {
        if (!bricks[i].destroyed)
        {
            SDL_Rect rect = {bricks[i].pos.x, bricks[i].pos.y, bricks[i].width, bricks[i].height};
            SDL_BlitSurface(brickSprite, &bricks[i].srcRect, window_surface, &rect);
        }
    }
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        perror("Error while initializing SDL");
        return 1;
    }

    init();

    // Charger les niveaux
    load_level("../Levels/niveautest.txt", bricks, &brick_count);

    bool quit = false;
    while (!quit)
    {
        SDL_PumpEvents();
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT])
            strafe_left(&_paddle);
        if (keys[SDL_SCANCODE_RIGHT])
            strafe_right(&_paddle);
        if (keys[SDL_SCANCODE_ESCAPE])
            quit = true;

        move_ball(&_ball);
        paddle_collide_walls(&_paddle, window_surface->w);
        ball_collide_walls(&_ball, &window_surface->clip_rect);
        ball_collide_paddle(&_ball, &_paddle.rect);
        draw();
        SDL_UpdateWindowSurface(window);
        now = SDL_GetPerformanceCounter();
        delta_t = 1.0 / FPS - (double)(now - prev) / (double)SDL_GetPerformanceFrequency();
        prev = now;
        if (delta_t > 0)
            SDL_Delay((Uint32)(delta_t * 1000));
        prev = SDL_GetPerformanceCounter();
    }

    SDL_Quit();
    return 0;
}

//
// Created by alexa on 3/7/2024.
//

#include <SDL_version.h>
#include "../includes/ball.h"
#include <stdbool.h>

ball create_ball(){
    ball b = {
        {300, 300, 24, 24},
        {10, 10}
    };
    return b;
}

void invert_x_speed(ball *b){
    b->v.x *= -1;
}

void invert_y_speed(ball *b){
    b->v.y *= -1;
}

void move_ball(ball *b){
    b->rect.x += b->v.x;
    b->rect.y += b->v.y;
}




void ball_collide_walls(ball *b, SDL_Rect *rect){
  if (b->rect.x < rect->x || b->rect.x > rect->w - 25){
    invert_x_speed(b);
  }
  else if (b->rect.y < rect->y || b->rect.y > rect->h - 25){
    invert_y_speed(b);
  }
}


float max(float a, float b){
  if (a > b){
    return a;
  }
  return b;
}

void ball_collide_rect(ball *b, SDL_Rect *r1){
    ball next = *b;
    move_ball(&next);

    const SDL_Point check_pos[4] = {
        {r1->x, r1->y},
        {r1->x + r1->w, r1->y},
        {r1->x, r1->y + r1->h},
        {r1->x + r1->w, r1->y + r1->h}
    };

    for (int i = 0; i < 4; i++){
        const SDL_Point p1 = {check_pos[i].x, check_pos[i].y};
        const SDL_Point p2 = {next.rect.x + 24, next.rect.y + 24};
        if (SDL_PointInRect(&p1, r1) || SDL_PointInRect(&p2, r1)) {
            const SDL_Rect r2 = {b->rect.x, b->rect.y, 24, 24};
            SDL_Rect res = {0, 0, 0, 0};
            if (SDL_IntersectRect(&r2, r1, &res)) {
                if (res.w > res.h) {
                    invert_y_speed(b);
                } else {
                    invert_x_speed(b);
                }
            }
            return;
        }
    }
}

bool is_point_inside_rect(SDL_Point p, SDL_Rect *r) {
    return (p.x >= r->x && p.x <= r->x + r->w && p.y >= r->y && p.y <= r->y + r->h);
}


//  SDL_Rect r2 = {b->x, b->y, 24, 24};
//  SDL_Rect res = {0, 0, 0, 0};
//  // if the ball collides horizontally, return HORZ
//  if (SDL_IntersectRect(&r2, r1, &res))
//  {
//    if (res.w > res.h)
//    {
//      invert_x_speed(b);
//    }
//    else if (res.w < res.h)
//    {
//      invert_y_speed(b);
//    }
//    else {
//      invert_x_speed(b);
//      invert_y_speed(b);
//    }
//  }
//  else {
//    // create a rectangle from the ball to next position
//    SDL_Rect r3 = {b->x + b->v.x, b->y + b->v.y, 24, 24};
//    if (SDL_IntersectRect(&r3, r1, &res)) {
//      if (res.w > res.h) { // ball collides horizontally
//        invert_y_speed(b);
//      } else if (res.w < res.h) { // ball collides vertically
//        invert_y_speed(b);
//      }
//    }
//
//  }

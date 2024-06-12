//
// Created by Sebastien on 03/06/2024.
//

#ifndef ARKANOID_SPRITECONSTANT_H
#define ARKANOID_SPRITECONSTANT_H
#include <SDL2/SDL.h>

extern SDL_Rect srcBg;
extern SDL_Rect srcBall;
extern SDL_Rect srcVaiss[8];

extern SDL_Rect whiteBrick;
extern SDL_Rect orangeBrick;
extern SDL_Rect cyanBrick;
extern SDL_Rect lightGreenBrick;
extern SDL_Rect darkBlueBrick;
extern SDL_Rect darkGreenBrick;
extern SDL_Rect lightRedBrick;
extern SDL_Rect blueBrick;
extern SDL_Rect pinkBrick;
extern SDL_Rect yellowBrick;
extern SDL_Rect darkRedBrick;
extern SDL_Rect darkCyanBrick;
extern SDL_Rect goldenBrickStates[6];
extern SDL_Rect silverBrickStates[6];
extern SDL_Rect defaultBrick;

//Bonus
extern SDL_Rect S_bonus_states[6];
extern SDL_Rect C_bonus_states[6];
extern SDL_Rect L_bonus_states[6];
extern SDL_Rect E_bonus_states[6];
extern SDL_Rect D_bonus_states[6];
extern SDL_Rect B_bonus_states[6];
extern SDL_Rect P_bonus_states[6];

//Backgrounds
extern SDL_Rect backgrounds[12];

//Tubes
extern SDL_Rect tube_v;
extern SDL_Rect tube_h;
extern SDL_Rect big_tube_v;
extern SDL_Rect big_tube_h;
extern SDL_Rect corner_top_left;
extern SDL_Rect corner_top_right;
extern SDL_Rect corner_bottom_right;
extern SDL_Rect corner_bottom_left;

// Lettres de l'alphabet
extern SDL_Rect A;
extern SDL_Rect B;
extern SDL_Rect C;
extern SDL_Rect D;
extern SDL_Rect E;
extern SDL_Rect F;
extern SDL_Rect G;
extern SDL_Rect H;
extern SDL_Rect I;
extern SDL_Rect J;
extern SDL_Rect K;
extern SDL_Rect L;
extern SDL_Rect M;
extern SDL_Rect N;
extern SDL_Rect O;
extern SDL_Rect P;
extern SDL_Rect Q;
extern SDL_Rect R;
extern SDL_Rect S;
extern SDL_Rect T;
extern SDL_Rect U;
extern SDL_Rect V;
extern SDL_Rect W;
extern SDL_Rect X;
extern SDL_Rect Y;
extern SDL_Rect Z;

// Chiffres de 0 à 9
extern SDL_Rect _0;
extern SDL_Rect _1;
extern SDL_Rect _2;
extern SDL_Rect _3;
extern SDL_Rect _4;
extern SDL_Rect _5;
extern SDL_Rect _6;
extern SDL_Rect _7;
extern SDL_Rect _8;
extern SDL_Rect _9;




#endif //ARKANOID_SPRITECONSTANT_H

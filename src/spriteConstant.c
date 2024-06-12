//
// Created by Sebastien on 03/06/2024.
//
#include "spriteConstant.h"

SDL_Rect srcBg = {0, 128, 96, 128}; // x,y, w,h (0,0) en haut a gauche
SDL_Rect srcBall = {4, 68, 8, 8};
SDL_Rect srcVaiss[8] = {
        {384, 128, 64, 16},
        {384,144, 74, 16},
        {384,160, 82, 16},
        {384,176, 90, 16},
        {384,192, 98, 16},
        {384,176, 108, 16},
        {384,176, 118, 16},
        {384,176, 128, 16}
};

//Bricks
SDL_Rect whiteBrick = {0, 0, 32, 16};
SDL_Rect orangeBrick = {32, 0, 32, 16};
SDL_Rect cyanBrick = {64, 0, 32, 16};
SDL_Rect lightGreenBrick = {96, 0, 32, 16};
SDL_Rect darkBlueBrick = {128, 0, 32, 16};
SDL_Rect darkGreenBrick = {160, 0, 32, 16};
SDL_Rect lightRedBrick = {0, 16, 32, 16};
SDL_Rect blueBrick = {32, 16, 32, 16};
SDL_Rect pinkBrick = {64, 16, 32, 16};
SDL_Rect yellowBrick = {96, 16, 32, 16};
SDL_Rect darkRedBrick = {128, 16, 32, 16};
SDL_Rect darkCyanBrick = {160, 16, 32, 16};
SDL_Rect defaultBrick = {0, 0, 0, 0};

SDL_Rect goldenBrickStates[6] = {
        {0, 48, 32, 16},
        {32, 48, 32, 16},
        {64, 48, 32, 16},
        {96, 48, 32, 16},
        {128, 48, 32, 16},
        {160, 48, 32, 16}
};

SDL_Rect silverBrickStates[6] = {
        {0, 32, 32, 16},
        {32, 32, 32, 16},
        {64, 32, 32, 16},
        {96, 32, 32, 16},
        {128, 32, 32, 16},
        {160, 32, 32, 16}
};

SDL_Rect S_bonus_states[6] = {
        {256,0, 32, 16},
        {288,0, 32, 16},
        {320,0, 32, 16},
        {352,0, 32, 16},
        {384,0, 32, 16},
        {416,0, 32, 16}
};
SDL_Rect C_bonus_states[6] = {
        {256,16, 32, 16},
        {288,16, 32, 16},
        {320,16, 32, 16},
        {352,16, 32, 16},
        {384,16, 32, 16},
        {416,16, 32, 16}
};
SDL_Rect L_bonus_states[6] = {
        {256,32, 32, 16},
        {288,32, 32, 16},
        {320,32, 32, 16},
        {352,32, 32, 16},
        {384,32, 32, 16},
        {416,32, 32, 16}
};
SDL_Rect E_bonus_states[6] = {
        {256,48, 32, 16},
        {288,48, 32, 16},
        {320,48, 32, 16},
        {352,48, 32, 16},
        {384,48, 32, 16},
        {416,48, 32, 16}
};
SDL_Rect D_bonus_states[6] = {
        {256,64, 32, 16},
        {288,64, 32, 16},
        {320,64, 32, 16},
        {352,64, 32, 16},
        {384,64, 32, 16},
        {416,64, 32, 16}
};
SDL_Rect B_bonus_states[6] = {
        {256,80, 32, 16},
        {288,80, 32, 16},
        {320,80, 32, 16},
        {352,80, 32, 16},
        {384,80, 32, 16},
        {416,80, 32, 16}
};
SDL_Rect P_bonus_states[6] = {
        {256,96, 32, 16},
        {288,96, 32, 16},
        {320,96, 32, 16},
        {352,96, 32, 16},
        {384,96, 32, 16},
        {416,96, 32, 16}
};

//Backgrounds
SDL_Rect backgrounds[12] = {
        {0, 128, 48, 64}, //default
        {0, 192, 48, 64}, //default dark
        {64, 128, 64, 64}, //blue
        {64, 192, 64, 64}, //blue dark
        {128, 128, 64, 64}, //green
        {128, 192, 64, 64}, //green dark
        {192, 128, 64, 64}, //red
        {192, 192, 64, 64}, //red dark
        {256, 128, 64, 64}, //orange
        {256, 192, 64, 64}, //orange dark
        {320, 128, 64, 64}, //purple
        {320, 192, 64, 64} //purple dark
};

SDL_Rect tube_v = {192, 48, 16, 32};
SDL_Rect tube_h = {208, 16, 32, 16};
SDL_Rect big_tube_v = {192, 0, 16, 48};
SDL_Rect big_tube_h = {208, 32, 48, 16};
SDL_Rect corner_top_left = {208,0,16,16};
SDL_Rect corner_top_right = {224,0,16,16};
SDL_Rect corner_bottom_right = {224,48,16,16};
SDL_Rect corner_bottom_left = {208,48,16,16};

SDL_Rect _0 = {0, 32, 32, 32};
SDL_Rect _1 = {32, 32, 32, 32};
SDL_Rect _2 = {64, 32, 32, 32};
SDL_Rect _3 = {96, 32, 32, 32};
SDL_Rect _4 = {128, 32, 32, 32};
SDL_Rect _5 = {160, 32, 32, 32};
SDL_Rect _6 = {192, 32, 32, 32};
SDL_Rect _7 = {224, 32, 32, 32};
SDL_Rect _8 = {256, 32, 32, 32};
SDL_Rect _9 = {288, 32, 32, 32};

// Définitions des lettres avec positions et dimensions spécifiées
SDL_Rect A = {32, 64, 32, 32};
SDL_Rect B = {64, 64, 32, 32};
SDL_Rect C = {96, 64, 32, 32};
SDL_Rect D = {128, 64, 32, 32};
SDL_Rect E = {160, 64, 32, 32};
SDL_Rect F = {192, 64, 32, 32};
SDL_Rect G = {224, 64, 32, 32};
SDL_Rect H = {256, 64, 32, 32};
SDL_Rect I = {288, 64, 32, 32};
SDL_Rect J = {320, 64, 32, 32};
SDL_Rect K = {352, 64, 32, 32};
SDL_Rect L = {384, 64, 32, 32};
SDL_Rect M = {416, 64, 32, 32};
SDL_Rect N = {448, 64, 32, 32};
SDL_Rect O = {480, 64, 32, 32};
SDL_Rect P = {0, 96, 32, 32};
SDL_Rect Q = {32, 96, 32, 32};
SDL_Rect R = {64, 96, 32, 32};
SDL_Rect S = {96, 96, 32, 32};
SDL_Rect T = {128, 96, 32, 32};
SDL_Rect U = {160, 96, 32, 32};
SDL_Rect V = {192, 96, 32, 32};
SDL_Rect W = {224, 96, 32, 32};
SDL_Rect X = {256, 96, 32, 32};
SDL_Rect Y = {288, 96, 32, 32};
SDL_Rect Z = {320, 96, 32, 32};
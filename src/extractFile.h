#ifndef EXTRACTFILE_H
#define EXTRACTFILE_H

#include "brick.h"
#include "spriteConstant.h"


SDL_Rect get_brick_src_rect(int brick_number, int level);
void load_level(const char *filename, brick bricks[], int *brick_count, int level);


#endif

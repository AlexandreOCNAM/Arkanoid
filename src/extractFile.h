#ifndef EXTRACTFILE_H
#define EXTRACTFILE_H

#include "spriteConstant.h"
#include "brick.h"


void extractFile(const char *inputFile, const char *outputFile);
void load_level(const char *filename, brick bricks[], int *brick_count);

#endif

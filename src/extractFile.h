#ifndef EXTRACTFILE_H
#define EXTRACTFILE_H

#include "brick.h"


void extractFile(const char *inputFile, const char *outputFile);
void load_level(const char *filename, Brick bricks[], int *brick_count);

#endif

#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

extern Camera3D camera;
extern int selectedBlock;
extern float BLOCK_SIZE;
extern unsigned int seed;

void InitWorld(void);
void DrawGUI(void);
void UnloadWorld(void);
void WorldBreakBlock(void);
void WorldPlaceBlock(void);
void Highlight(void);

#endif
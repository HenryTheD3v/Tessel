#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>
#include "chunk.h"

extern Camera3D camera;
extern int selectedBlock;
extern float BLOCK_SIZE;
extern Chunk testchunk;

void InitWorld(void);
void DrawGUI(void);
void UnloadWorld(void);
void WorldBreakBlock(void);
void WorldPlaceBlock(void);
void Highlight(void);

#endif
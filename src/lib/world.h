#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>


extern Camera3D camera;
extern int selectedBlock;

void InitWorld(void);
void DrawGUI(void);
void UnloadWorld(void);
void WorldBreakBlock(void);
void WorldPlaceBlock(void);

#endif
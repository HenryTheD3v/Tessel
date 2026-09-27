#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>


extern Camera3D camera;

void InitWorld(void);
void DrawGUI(void);
void UnloadWorld(void);

#endif
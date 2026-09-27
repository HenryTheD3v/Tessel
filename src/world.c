#include <raylib.h>
#include <stdio.h>
#include "lib/world.h"

#define WORLD_X 16
#define WORLD_Y 16
#define WORLD_Z 16

Model grass_block;
Texture2D grasstop_texture;

int world_data[WORLD_X][WORLD_Y][WORLD_Z];

Camera3D camera;

void InitWorld(void){
    camera = (Camera3D){ 0 };
    camera.position = (Vector3){4,5,0};
    camera.target = (Vector3){0,1,0};
    camera.up = (Vector3){0,1,0};
    camera.fovy = 120.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    Texture2D grasstop_texture = LoadTexture("assets/grasstop.png");
    Mesh grassMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    grass_block = LoadModelFromMesh(grassMesh);
    grass_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grasstop_texture;
}

void DrawWorld(void){
    DrawModel(grass_block, (Vector3){0, 0, 0}, 20.0f, WHITE);
}

void UnloadWorld(void){
    UnloadModel(grass_block);
    UnloadTexture(grasstop_texture);
}
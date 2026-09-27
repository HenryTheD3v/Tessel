#include <raylib.h>
#include <stdio.h>
#include "lib/world.h"

#define WORLD_X 16
#define WORLD_Y 16
#define WORLD_Z 16

Model grass_block;
Texture2D grasstop_texture;
Model dirt_block;
Texture2D dirt_texture;
Model missing_block;
Texture2D missing_texture;

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
    Texture2D dirt_texture = LoadTexture("assets/dirt.png");
    Texture2D missing_texture = LoadTexture("assets/missingtexture.png");
    Mesh grassMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    grass_block = LoadModelFromMesh(grassMesh);
    grass_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grasstop_texture;
    Mesh dirtMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    dirt_block = LoadModelFromMesh(dirtMesh);
    dirt_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = dirt_texture;
    Mesh missingMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    missing_block = LoadModelFromMesh(missingMesh);
    missing_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = missing_texture;
}

void DrawWorld(void){
    DrawModel(grass_block, (Vector3){0, 0, 0}, 20.0f, WHITE);
    DrawModel(dirt_block, (Vector3){-40, 0, 0}, 20.0f, WHITE);
    DrawModel(missing_block, (Vector3){40, 0, 0}, 20.0f, WHITE);
}

void UnloadWorld(void){
    UnloadModel(grass_block);
    UnloadTexture(grasstop_texture);
}
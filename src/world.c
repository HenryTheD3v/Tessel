#include <raylib.h>
#include <stdio.h>
#include "lib/world.h"
#include <math.h>

#define WORLD_X 16
#define WORLD_Y 16
#define WORLD_Z 16
#define BLOCK_SIZE 20.0f


// Nothing is 0
// Grass is 1
// Dirt is 2
// Stone is 3

// Model Declaration
Model grass_block;
Model dirt_block;
Model missing_block;
Model stone_block;


// Texture Declaration
Texture2D grasstop_texture;
Texture2D dirt_texture;
Texture2D missing_texture;
Texture2D stone_texture;


int selectedBlock = 1;
int world_data[WORLD_X][WORLD_Y][WORLD_Z];

Camera3D camera;

void InitWorld(void){
    camera = (Camera3D){ 0 };
    camera.position = (Vector3){4,5,0};
    camera.target = (Vector3){0,1,0};
    camera.up = (Vector3){0,1,0};
    camera.fovy = 120.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Texture Loading
    grasstop_texture = LoadTexture("assets/grasstop.png");
    dirt_texture = LoadTexture("assets/dirt.png");
    missing_texture = LoadTexture("assets/missingtexture.png");
    stone_texture = LoadTexture("assets/stone.png");

    // Mesh Declaration
    Mesh grassMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Mesh dirtMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Mesh missingMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Mesh stoneMesh = GenMeshCube(1.0f, 1.0f, 1.0f);

    // Model Loading
    grass_block = LoadModelFromMesh(grassMesh);
    dirt_block = LoadModelFromMesh(dirtMesh);
    missing_block = LoadModelFromMesh(missingMesh);
    stone_block = LoadModelFromMesh(stoneMesh);

    // Texture Mapping
    grass_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grasstop_texture;
    dirt_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = dirt_texture;
    missing_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = missing_texture;
    stone_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = stone_texture;

    // World Data
    for (int x = 0; x < WORLD_X; x++){
        for (int z = 0; z < WORLD_Z; z++){
            world_data[x][0][z] = 3;
            world_data[x][1][z] = 3;
            world_data[x][2][z] = 3;
            world_data[x][3][z] = 2;
            world_data[x][4][z] = 2;
            world_data[x][5][z] = 2;
            world_data[x][6][z] = 1;
        }
    }
}

void DrawWorld(void){
    for (int x = 0; x < WORLD_X; x++){
        for (int y = 0; y < WORLD_Y; y++){
            for (int z = 0; z < WORLD_Z; z++){
        if(world_data[x][y][z] == 0){
            continue;
        }
        if(world_data[x][y][z] == 1){
            DrawModel(
                grass_block,
                (Vector3) {
                    x * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    y * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    z * BLOCK_SIZE + BLOCK_SIZE / 2.0f
                },
                20.0f,
                WHITE
            );
        }
        else if(world_data[x][y][z] == 2){
            DrawModel(
                dirt_block,
                (Vector3) {
                    x * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    y * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    z * BLOCK_SIZE + BLOCK_SIZE / 2.0f
                },
                20.0f,
                WHITE
            );
        } else if(world_data[x][y][z] == 3){
            DrawModel(
                stone_block,
                (Vector3) {
                    x * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    y * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    z * BLOCK_SIZE + BLOCK_SIZE / 2.0f
                },
                20.0f,
                WHITE
            );
        } else {
            DrawModel(
                    missing_block,
                (Vector3) {
                    x * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    y * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    z * BLOCK_SIZE + BLOCK_SIZE / 2.0f
                },
                20.0f,
                WHITE
            );
        }
        }
        }
    }
}

void WorldBreakBlock(void){
    Ray ray = GetMouseRay((Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},camera);
    Vector3 position = ray.position;
    for (float dist = 0; dist < 160.0f; dist += 0.2f){
        position.x = ray.position.x + ray.direction.x * dist;
        position.y = ray.position.y + ray.direction.y * dist;
        position.z = ray.position.z + ray.direction.z * dist;

        int blockX = (int)floorf(position.x / BLOCK_SIZE);
        int blockY = (int)floorf(position.y / BLOCK_SIZE);
        int blockZ = (int)floorf(position.z / BLOCK_SIZE);

        if (blockX < 0 || blockX >= WORLD_X ||
            blockY < 0 || blockY >= WORLD_Y ||
            blockZ < 0 || blockZ >= WORLD_Z)
        {
            continue;
        }

        if(world_data[blockX][blockY][blockZ] != 0 ){
            world_data[blockX][blockY][blockZ] = 0;
            return;
        }
    }
}

void WorldPlaceBlock(void){
    int lastX = (int)floorf(camera.position.x / BLOCK_SIZE);
    int lastY = (int)floorf(camera.position.y / BLOCK_SIZE);
    int lastZ = (int)floorf(camera.position.z / BLOCK_SIZE);
    Ray ray = GetMouseRay((Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},camera);
    Vector3 position = ray.position;
    for (float dist = 0; dist < 160.0f; dist += 0.2f){
        position.x = ray.position.x + ray.direction.x * dist;
        position.y = ray.position.y + ray.direction.y * dist;
        position.z = ray.position.z + ray.direction.z * dist;

        int blockX = (int)floorf(position.x / BLOCK_SIZE);
        int blockY = (int)floorf(position.y / BLOCK_SIZE);
        int blockZ = (int)floorf(position.z / BLOCK_SIZE);

        if (blockX < 0 || blockX >= WORLD_X ||
            blockY < 0 || blockY >= WORLD_Y ||
            blockZ < 0 || blockZ >= WORLD_Z)
        {
            continue;
        }

        if(world_data[blockX][blockY][blockZ] != 0 ){
            world_data[lastX][lastY][lastZ] = selectedBlock;
            return;
        } else {
            lastX = blockX;
            lastY = blockY;
            lastZ = blockZ;
        }
    }
}



void UnloadWorld(void){
    UnloadModel(grass_block);
    UnloadTexture(grasstop_texture);
    UnloadModel(dirt_block);
    UnloadTexture(dirt_texture);
    UnloadModel(missing_block);
    UnloadTexture(missing_texture);
    UnloadModel(stone_block);
    UnloadTexture(stone_texture);
}
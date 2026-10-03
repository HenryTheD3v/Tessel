#include <raylib.h>
#include <stdio.h>
#include "lib/world.h"
#include "lib/chunk.h"
#include <math.h>

#define WORLD_X 16
#define WORLD_Y 16
#define WORLD_Z 16
#define CHUNK_X 16
#define CHUNK_Y 16
#define CHUNK_Z 16

// temp test for chunks
int id = 2;

float BLOCK_SIZE = 20.0f;


// Nothing is 0
// Grass is 1
// Dirt is 2
// Stone is 3

// Model Declaration
Model grass_block;
Model dirt_block;
Model missing_block;
Model stone_block;
Model sand_block;


// Texture Declaration
Texture2D grasstop_texture;
Texture2D dirt_texture;
Texture2D missing_texture;
Texture2D stone_texture;
Texture2D sand_texture;

// Test Chunks
Chunk testchunk;


int selectedBlock = 1;


Camera3D camera;

void InitWorld(void){
    camera = (Camera3D){ 0 };
    camera.position = (Vector3){7*20,12*20,7*20};
    camera.target = (Vector3){0,1,0};
    camera.up = (Vector3){0,1,0};
    camera.fovy = 120.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Texture Loading
    grasstop_texture = LoadTexture("assets/grasstop.png");
    dirt_texture = LoadTexture("assets/dirt.png");
    missing_texture = LoadTexture("assets/missingtexture.png");
    stone_texture = LoadTexture("assets/stone.png");
    sand_texture = LoadTexture("assets/sand.png");

    // Mesh Declaration
    Mesh grassMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Mesh dirtMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Mesh missingMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Mesh stoneMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Mesh sandMesh = GenMeshCube(1.0f, 1.0f, 1.0f);

    // Model Loading
    grass_block = LoadModelFromMesh(grassMesh);
    dirt_block = LoadModelFromMesh(dirtMesh);
    missing_block = LoadModelFromMesh(missingMesh);
    stone_block = LoadModelFromMesh(stoneMesh);
    sand_block = LoadModelFromMesh(sandMesh);

    // Texture Mapping
    grass_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grasstop_texture;
    dirt_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = dirt_texture;
    missing_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = missing_texture;
    stone_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = stone_texture;
    sand_block.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = sand_texture;

    // World Data
    
    InitChunk(&testchunk, -1, 0, id);
}

void DrawWorld(void){
    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int y = 0; y < CHUNK_SIZE; y++){
            for(int z = 0; z < CHUNK_SIZE; z++){
                int blockID = testchunk.blocks[x][y][z];

                if(blockID == 0)
                    continue;
                
                int worldX = testchunk.x * CHUNK_SIZE + x;
                int worldZ = testchunk.z * CHUNK_SIZE + z;

                Vector3 position = {
                    worldX * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    y * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    worldZ * BLOCK_SIZE + BLOCK_SIZE / 2.0f
                };

                if(blockID == 1){
                    DrawModel(
                    grass_block,
                    position,
                    BLOCK_SIZE,
                    WHITE
                    );
                } else if(blockID == 2){
                    DrawModel(
                    dirt_block,
                    position,
                    BLOCK_SIZE,
                    WHITE
                    );
                } else if(blockID == 3){
                    DrawModel(
                    stone_block,
                    position,
                    BLOCK_SIZE,
                    WHITE
                    );
                } else if(blockID == 4){
                    DrawModel(
                    sand_block,
                    position,
                    BLOCK_SIZE,
                    WHITE
                    );
                } else {
                    DrawModel(
                    missing_block,
                    position,
                    BLOCK_SIZE,
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
    for (float dist = 0; dist < 120.0f; dist += 0.2f){
        position.x = ray.position.x + ray.direction.x * dist;
        position.y = ray.position.y + ray.direction.y * dist;
        position.z = ray.position.z + ray.direction.z * dist;

        int blockX = (int)floorf(position.x / BLOCK_SIZE);
        int blockY = (int)floorf(position.y / BLOCK_SIZE);
        int blockZ = (int)floorf(position.z / BLOCK_SIZE);

        if(GetBlock(blockX, blockY, blockZ) != 0 ){
            SetBlock(blockX, blockY, blockZ, 0);
            return;
        }
    }
}

void WorldPlaceBlock(void){
    int64_t lastX = (int64_t)floorf(camera.position.x / BLOCK_SIZE);
    int64_t lastY = (int64_t)floorf(camera.position.y / BLOCK_SIZE);
    int64_t lastZ = (int64_t)floorf(camera.position.z / BLOCK_SIZE);
    Ray ray = GetMouseRay((Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},camera);
    Vector3 position = ray.position;
    for (float dist = 0; dist < 160.0f; dist += 0.2f){
        position.x = ray.position.x + ray.direction.x * dist;
        position.y = ray.position.y + ray.direction.y * dist;
        position.z = ray.position.z + ray.direction.z * dist;

        int blockX = (int)floorf(position.x / BLOCK_SIZE);
        int blockY = (int)floorf(position.y / BLOCK_SIZE);
        int blockZ = (int)floorf(position.z / BLOCK_SIZE);

        if(GetBlock(blockX, blockY, blockZ) != 0 ){
            SetBlock(lastX, lastY, lastZ, selectedBlock);
            return;
        } else {
            lastX = blockX;
            lastY = blockY;
            lastZ = blockZ;
        }
    }
}

void Highlight(void){
    Ray ray = GetMouseRay((Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},camera);
    Vector3 position = ray.position;
    for (float dist = 0; dist < 120.0f; dist += 0.2f){
        position.x = ray.position.x + ray.direction.x * dist;
        position.y = ray.position.y + ray.direction.y * dist;
        position.z = ray.position.z + ray.direction.z * dist;

        int blockX = (int)floorf(position.x / BLOCK_SIZE);
        int blockY = (int)floorf(position.y / BLOCK_SIZE);
        int blockZ = (int)floorf(position.z / BLOCK_SIZE);

        if(GetBlock(blockX, blockY, blockZ) != 0 ){
            DrawCube(
                (Vector3){
                    blockX * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    blockY * BLOCK_SIZE + BLOCK_SIZE / 2.0f,
                    blockZ * BLOCK_SIZE + BLOCK_SIZE / 2.0f
                },
                20.1f,
                20.1f,
                20.1f,
                (Color){255, 255, 255, 128}
            );
            return;
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
    UnloadModel(sand_block);
    UnloadTexture(sand_texture);
}
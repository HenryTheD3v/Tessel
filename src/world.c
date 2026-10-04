#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>
#include "lib/world.h"
#include "lib/chunk.h"
#include "lib/player.h"
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
// Sand is 4

// Texture Declaration
Texture2D grasstop_texture;
Texture2D dirt_texture;
Texture2D missing_texture;
Texture2D stone_texture;
Texture2D sand_texture;
Texture2D block_textures[5];

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

    block_textures[0] = missing_texture;
    block_textures[1] = grasstop_texture;
    block_textures[2] = dirt_texture;
    block_textures[3] = stone_texture;
    block_textures[4] = sand_texture;

    CreateChunkGrid(-1, 0, 10, 10, id);
}

void DrawWorld(void){
    UpdateChunks(BLOCK_SIZE, block_textures);
    DrawChunks();
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
            if(GetBlock(lastX, lastY, lastZ) == 0){
                if(player.position.x < lastX + 1 && player.position.x > lastX &&
                    player.position.y < lastY + 2 && player.position.y > lastY &&
                    player.position.z < lastZ + 1 && player.position.z > lastZ){
                    return;
                }
                SetBlock(lastX, lastY, lastZ, selectedBlock);
            }
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
    ClearChunks();
    UnloadTexture(grasstop_texture);
    UnloadTexture(dirt_texture);
    UnloadTexture(missing_texture);
    UnloadTexture(stone_texture);
    UnloadTexture(sand_texture);
}
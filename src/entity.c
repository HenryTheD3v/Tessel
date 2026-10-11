#include <raylib.h>
#include "lib/entity.h"
#include "lib/chunk.h"
#include "lib/world.h"
#include "lib/player.h"
#include <math.h>

Model test;

Entity entity = {
    .position = { 8.0f, 20.0f, 8.0f},
    .velocity = { 0 },
    .rotation = { 0, 0 },
    .width = 0.6f,
    .height = 1.8f,
    .gravity = 20.0f,
    .friction = 8.0f,
    .grounded = false,
    .ismoving = false
};

bool CheckEntityCollision(Vector3 position)
{
    float minX = position.x - entity.width / 2.0f;
    float maxX = position.x + entity.width / 2.0f;

    float minY = position.y;
    float maxY = position.y + entity.height;

    float minZ = position.z - entity.width / 2.0f;
    float maxZ = position.z + entity.width / 2.0f;

    int startX = (int)floorf(minX);
    int endX   = (int)floorf(maxX);

    int startY = (int)floorf(minY);
    int endY   = (int)floorf(maxY);

    int startZ = (int)floorf(minZ);
    int endZ   = (int)floorf(maxZ);

    for (int x = startX; x <= endX; x++) {
        for (int y = startY; y <= endY; y++) {
            for (int z = startZ; z <= endZ; z++) {

                if (GetBlock(x, y, z) != 0) {
                    return true;
                }

            }
        }
    }

    return false;
}


void InitEntities(void){
    test = LoadModel("assets/models/testentity.obj");
}

void DrawEntities(void){
    DrawModel(
        test,
        (Vector3){
        entity.position.x + 1 / 2.0f,
        entity.position.y + 1 / 2.0f * entity.height,
        entity.position.z + 1 / 2.0f
        },
        1.0f / 1.75f,
        WHITE
    );
}

void UpdateEntities(void){
    float dt = GetFrameTime();

    entity.velocity.y -= entity.gravity * dt;

    entity.position.x += entity.velocity.x * dt;

    if(CheckEntityCollision(entity.position)){
        entity.position.x -= entity.velocity.x * dt;
        entity.velocity.x = 0.0f;
    }

    entity.position.y += entity.velocity.y * dt;

    if(CheckEntityCollision(entity.position)){
        entity.position.y -= entity.velocity.y * dt;
        entity.velocity.y = 0.0f;
        entity.grounded = true;
    }

    entity.position.z += entity.velocity.z * dt;

    if(CheckEntityCollision(entity.position)){
        entity.position.z -= entity.velocity.z * dt;
        entity.velocity.z = 0.0f;
    }
}

void UnloadEntities(void){
    UnloadModel(test);
}
#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "lib/player.h"
#include "lib/world.h"
#include "lib/chunk.h"
#include "lib/main.h"


Player player = {
    .position = { -13.0f, 20.0f, 13.0f},
    .velocity = { 0 },\
    .camera = { 0 },
    .rotation = { 0, 0 },
    .width = 0.6f,
    .height = 1.8f,
    .gravity = 20.0f,
    .friction = 8.0f,
    .grounded = false,
    .ismoving = false
};

bool debug = false;
float speedcap = 100.0f;

float sensitivity = 0.003f;
float acceleration = 40.0f;
float maxSpeed = 4.0f;
float maxSpeedn = 4.0f;
float sprint = 1.25f;
float x = 0;
float y = 0;
float z = 0;

float jumpheight = 8.0f;


bool CheckCollision(Vector3 position)
{
    float minX = position.x - player.width / 2.0f;
    float maxX = position.x + player.width / 2.0f;

    float minY = position.y;
    float maxY = position.y + player.height;

    float minZ = position.z - player.width / 2.0f;
    float maxZ = position.z + player.width / 2.0f;

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

void UpdatePlayer(void){
    float dt = GetFrameTime();
    Vector2 mouse = GetMouseDelta();
    player.rotation.x -= mouse.x * sensitivity; // yaw
    player.rotation.y -= mouse.y * sensitivity; // pitch
    Vector3 forward = {
        sinf(player.rotation.x),
        0.0f,
        cosf(player.rotation.x)
    };
    Vector3 right = {
        cosf(player.rotation.x),
        0.0f,
        -sinf(player.rotation.x)
    };
    
    player.ismoving = false;

    if (IsKeyDown(KEY_W)) {
        player.velocity.x += forward.x * acceleration * dt;
        player.velocity.z += forward.z * acceleration * dt;
        player.ismoving = true;
    }

    if (IsKeyDown(KEY_S)) {
        player.velocity.x -= forward.x * acceleration * dt;
        player.velocity.z -= forward.z * acceleration * dt;
        player.ismoving = true;
    }

    if (IsKeyDown(KEY_A)) {
        player.velocity.x += right.x * acceleration * dt;
        player.velocity.z += right.z * acceleration * dt;
        player.ismoving = true;
    }

    if (IsKeyDown(KEY_D)) {
        player.velocity.x -= right.x * acceleration * dt;
        player.velocity.z -= right.z * acceleration * dt;
        player.ismoving = true;
    }
    if(IsKeyDown(KEY_SPACE)){
        if(player.grounded){
            player.velocity.y = jumpheight;
            player.grounded = false;
        }
    }
    if(IsKeyDown(KEY_LEFT_SHIFT)){
        player.velocity.y -= acceleration * dt;
    }
    if(IsKeyPressed(KEY_R)){
        player.position.x = -13.0f;
        player.position.y = 20.0f;
        player.position.z = 13.0f;
    }
    if(IsKeyDown(KEY_LEFT_CONTROL)){
        maxSpeed = maxSpeedn * sprint;
    }else{
            maxSpeed = maxSpeedn;
        }
    
    if(IsKeyDown(KEY_ESCAPE)){
        active = false;
    }
    if(IsKeyDown(KEY_ONE)){
        selectedBlock = 1;
    }
    if(IsKeyDown(KEY_TWO)){
        selectedBlock = 2;
    }
    if(IsKeyDown(KEY_THREE)){
        selectedBlock = 3;
    }
    if(IsKeyDown(KEY_FOUR)){
        selectedBlock = 4;
    }

    // Debug Keybinds
    if(IsKeyPressed(KEY_F3)){
        debug = !debug;
    }
    if(IsKeyDown(KEY_M)){
        player.grounded = true;
    }




    
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        WorldBreakBlock();
    }
    
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        WorldPlaceBlock();
    }

    player.velocity.y -= player.gravity * dt;

    if(player.rotation.y > 1.5f){
        player.rotation.y = 1.5f;
    }
    if(player.rotation.y < -1.5){
        player.rotation.y = -1.5f;
    }

    float horizontalSpeed = sqrtf(
        player.velocity.x * player.velocity.x +
        player.velocity.z * player.velocity.z
    );

    if (horizontalSpeed > maxSpeed) {
        float scale = maxSpeed / horizontalSpeed;

        player.velocity.x *= scale;
        player.velocity.z *= scale;
    }
        float frictionFactor = fmaxf(0.0f, 1.0f - player.friction * dt);
        if(!player.ismoving){
            player.velocity.x *= frictionFactor;
            player.velocity.z *= frictionFactor;
        }
    
    player.position.x += player.velocity.x * dt;

    if(CheckCollision(player.position)){
        player.position.x -= player.velocity.x * dt;
        player.velocity.x = 0.0f;
    }

    player.position.y += player.velocity.y * dt;

    if(CheckCollision(player.position)){
        player.position.y -= player.velocity.y * dt;
        player.velocity.y = 0.0f;
        player.grounded = true;
    }

    player.position.z += player.velocity.z * dt;

    if(CheckCollision(player.position)){
        player.position.z -= player.velocity.z * dt;
        player.velocity.z = 0.0f;
    }
    
    player.camera.x = player.position.x;
    player.camera.y = player.position.y + player.height / 1.25f;
    player.camera.z = player.position.z;

    camera.position.x = player.camera.x * BLOCK_SIZE;
    camera.position.y = player.camera.y * BLOCK_SIZE;
    camera.position.z = player.camera.z * BLOCK_SIZE;
    camera.target.x = camera.position.x + cosf(player.rotation.y) * sinf(player.rotation.x);
    camera.target.y = camera.position.y + sinf(player.rotation.y);
    camera.target.z = camera.position.z + cosf(player.rotation.y) * cosf(player.rotation.x);
}
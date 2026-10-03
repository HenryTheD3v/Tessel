#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "lib/player.h"
#include "lib/world.h"
#include "lib/main.h"


Player player = {
    .position = { 7.0f, 12.0f, 7.0f},
    .velocity = { 0 },
    .width = 12.0f,
    .height = 36.0f,
    .grounded = false
};



float yaw = 0.0f;
float pitch = 0.0f;
float sensitivity = 0.003f;
float speed = 8.0f;
float speedn = 8.0f;
float sprint = 2.0f;
float x = 0;
float y = 0;
float z = 0;

float velocityX = 0.0f;
float velocityY = 0.0f;
float velocityZ = 0.0f;
float gravity = 1.0f;
bool grounded = false;
float jumpheight = 1.0f;
bool canjump = true;



void UpdatePlayer(void){
    float dt = GetFrameTime();
    Vector2 mouse = GetMouseDelta();
    yaw -= mouse.x * sensitivity;
    pitch -= mouse.y * sensitivity;
    Vector3 forward = {
        sinf(yaw),
        0.0f,
        cosf(yaw)
    };
    Vector3 right = {
        cosf(yaw),
        0.0f,
        -sinf(yaw)
    };
    if(IsKeyDown(KEY_W)){
        player.position.x += forward.x * speed * dt;
        player.position.z += forward.z * speed * dt;
    }
    if(IsKeyDown(KEY_S)){
        player.position.x -= forward.x * speed * dt;
        player.position.z -= forward.z * speed * dt;
    }
    if(IsKeyDown(KEY_A)){
        player.position.x += right.x * speed * dt;
        player.position.z += right.z * speed * dt;
    }
    if(IsKeyDown(KEY_D)){
        player.position.x -= right.x * speed * dt;
        player.position.z -= right.z * speed * dt;
    }
    if(IsKeyDown(KEY_SPACE)){
        /*
        if(canjump){
            grounded = false;
            velocityY = jumpheight;
        }
        */
        player.position.y += speed * dt;
    }
    if(IsKeyDown(KEY_LEFT_SHIFT)){
        player.position.y -= speed * dt;
    }
    if(IsKeyPressed(KEY_R)){
        player.position.x = 7;
        player.position.y = 12;
        player.position.z = 7;
    }
    if(IsKeyDown(KEY_LEFT_CONTROL)){
        speed = speedn * sprint;
    }else{
            speed = speedn;
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
    
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        WorldBreakBlock();
    }
    
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        WorldPlaceBlock();
    }
    

    /*
    velocityY -= gravity * dt;

    camera.position.y += velocityY;


    if(camera.position.y <= groundY){
        camera.position.y = groundY;
        velocityY = 0.0f;
        grounded = true;
        canjump = true;
    } else{
        grounded = false;
        canjump = false;
    }
    */

    if(pitch > 1.5f){
        pitch = 1.5f;
    }
    if(pitch < -1.5){
        pitch = -1.5f;
    }
    camera.position.x = player.position.x * BLOCK_SIZE;
    camera.position.y = player.position.y * BLOCK_SIZE + player.height / 2.0f;
    camera.position.z = player.position.z * BLOCK_SIZE;
    camera.target.x = camera.position.x + cosf(pitch) * sinf(yaw);
    camera.target.y = camera.position.y + sinf(pitch);
    camera.target.z = camera.position.z + cosf(pitch) * cosf(yaw);
}
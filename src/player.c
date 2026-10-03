#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "lib/player.h"
#include "lib/world.h"
#include "lib/main.h"

float yaw = 0.0f;
float pitch = 0.0f;
float sensitivity = 0.003f;
float speed = 65.0f;
float speedn = 65.0f;
float sprint = 3.0f;
float x = 0;
float y = 0;
float z = 0;

//float velocityX = 0;
float velocityY = 0.0f;
//float velocityZ = 0;
float gravity = 5.0f;
bool grounded = false;
float jumpheight = 2.0f;
bool canjump = true;



void UpdatePlayer(void){
    float dt = GetFrameTime();
    float groundY = 8.8f * BLOCK_SIZE;
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
        camera.position.x += forward.x * speed * dt;
        camera.position.z += forward.z * speed * dt;
    }
    if(IsKeyDown(KEY_S)){
        camera.position.x -= forward.x * speed * dt;
        camera.position.z -= forward.z * speed * dt;
    }
    if(IsKeyDown(KEY_A)){
        camera.position.x += right.x * speed * dt;
        camera.position.z += right.z * speed * dt;
    }
    if(IsKeyDown(KEY_D)){
        camera.position.x -= right.x * speed * dt;
        camera.position.z -= right.z * speed * dt;
    }
    if(IsKeyDown(KEY_SPACE)){
        /*
        if(canjump){
            grounded = false;
            velocityY = jumpheight;
        }
        */
        camera.position.y += speed * dt;
    }
    if(IsKeyDown(KEY_LEFT_SHIFT)){
        camera.position.y -= speed * dt;
    }
    if(IsKeyPressed(KEY_R)){
        camera.position.x = 7 * BLOCK_SIZE;
        camera.position.y = 12 * BLOCK_SIZE;
        camera.position.z = 7 * BLOCK_SIZE;
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

    camera.target.x = camera.position.x + cosf(pitch) * sinf(yaw);
    camera.target.y = camera.position.y + sinf(pitch);
    camera.target.z = camera.position.z + cosf(pitch) * cosf(yaw);
}
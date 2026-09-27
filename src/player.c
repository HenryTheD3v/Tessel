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
float x = 0;
float y = 0;
float z = 0;


void UpdatePlayer(void){\
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
        camera.position.y += speed * dt;
    }
    if(IsKeyDown(KEY_LEFT_SHIFT)){
        camera.position.y -= speed * dt;
    }
    if(IsKeyDown(KEY_LEFT_CONTROL)){
        speed = speedn * 1.5;
    }else{
            speed = speedn;
        }
    
    if(IsKeyDown(KEY_ESCAPE)){
        active = false;
    }
    camera.target.x = camera.position.x + cosf(pitch) * sinf(yaw);
    camera.target.y = camera.position.y + sinf(pitch);
    camera.target.z = camera.position.z + cosf(pitch) * cosf(yaw);
    if(pitch > 1.5f){
        pitch = 1.5f;
    }
    if(pitch < -1.5){
        pitch = -1.5f;
    }
}

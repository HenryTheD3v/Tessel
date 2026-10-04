#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <stdbool.h>

typedef struct {
    Vector3 position;
    Vector3 velocity;
    Vector3 camera;
    Vector2 rotation;

    float width;
    float height;
    float gravity;
    float friction;

    bool grounded;
    bool ismoving;
} Player;

extern float yaw;
extern float pitch;
extern bool debug;

extern Player player;

void UpdatePlayer(void);

#endif
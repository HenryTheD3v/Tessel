#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <stdbool.h>

typedef struct {
    Vector3 position;
    Vector3 velocity;

    float width;
    float height;

    bool grounded;
} Player;

extern float yaw;
extern float pitch;

extern Player player;

void UpdatePlayer(void);

#endif
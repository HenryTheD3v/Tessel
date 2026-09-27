#include <raylib.h>
#include <stdio.h>
#include "lib/main.h"
#include "lib/gui.h"
#include "lib/world.h"
#include "lib/player.h"
#include <stdbool.h>
#include <math.h>

Vector2 res = {1280/1.5, 720/1.5};
bool active = true;



int main(void)
{
    SetTargetFPS(120);
    InitWindow(res.x, res.y, "Tessel");
    InitGUI();
    InitWorld();
    DisableCursor();

    while (active)
    {

        
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);

        UpdatePlayer();
        DrawWorld();
        
        EndMode3D();
        DrawGUI();
        EndDrawing();
    }

    CloseWindow();
    UnloadGUI();
    UnloadWorld();

    return 0;
}
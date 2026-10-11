#include <raylib.h>
#include <stdio.h>
#include <stdint.h>
#include "lib/main.h"
#include "lib/gui.h"
#include "lib/world.h"
#include "lib/player.h"
#include "lib/entity.h"
#include <stdbool.h>
#include <math.h>

Vector2 res = {1280/1.25, 720/1.25};
bool active = true;



int main(void)
{
    SetTargetFPS(120);
    InitWindow(res.x, res.y, "Tessel");
    InitGUI();
    InitWorld();
    InitEntities();
    DisableCursor();

    while (active)
    {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);

        UpdatePlayer();
        UpdateEntities();
        DrawWorld();
        DrawEntities();
        
        BeginBlendMode(BLEND_ALPHA);
        Highlight();
        EndBlendMode();
        
        EndMode3D();
        DrawGUI();
        EndDrawing();
    }

    CloseWindow();
    UnloadEntities();
    UnloadGUI();
    UnloadWorld();

    return 0;
}
#include <raylib.h>
#include "lib/gui.h"
#include "lib/player.h"
#include "lib/world.h"

static Texture2D crosshair;
static Texture2D grass;
static Texture2D dirt;
static Texture2D stone;

void InitGUI(void){
    crosshair = LoadTexture("assets/crosshair.png");
    grass = LoadTexture("assets/grasstop.png");
    dirt = LoadTexture("assets/dirt.png");
    stone = LoadTexture("assets/stone.png");
}

void DrawGUI(void){
    int screenwidth = GetScreenWidth();
    int screenheight = GetScreenHeight();

    float size = 1.0f;

    DrawTextureEx(crosshair,
    (Vector2){
        screenwidth/2 - crosshair.width * size / 2.0f,
        screenheight/2 - crosshair.height * size / 2.0f
    },
    0.0f,
    size,
    (Color){255, 255, 255, 128});
    DrawText("MCTEST", 20, 20, 40, WHITE);
    int fps = GetFPS();
    DrawText(TextFormat("FPS: %d",fps), 20, 60, 40, WHITE);
    DrawText(TextFormat("Yaw: %.3f Pitch: %.3f",yaw, pitch), 20, 100, 40, WHITE);
    DrawText(TextFormat("X: %.3f Y: %.3f Z: %.3f",camera.position.x, camera.position.y, camera.position.z), 20, 140, 40, WHITE);
    if(selectedBlock == 1){
        DrawTextureEx(grass,
        (Vector2){
            screenwidth - 20 - grass.height * 5,
            20,
        },
        0.0f,
        5.0f,
        (Color){255, 255, 255, 128});
    } else if(selectedBlock == 2){
        DrawTextureEx(dirt,
        (Vector2){
            screenwidth - 20 - dirt.height * 5,
            20,
        },
        0.0f,
        5.0f,
        (Color){255, 255, 255, 128});
    } else if(selectedBlock == 3){
        DrawTextureEx(stone,
        (Vector2){
            screenwidth - 20 - stone.height * 5,
            20,
        },
        0.0f,
        5.0f,
        (Color){255, 255, 255, 128});
    }
}

void UnloadGUI(void){
    UnloadTexture(crosshair);
    UnloadTexture(grass);
    UnloadTexture(dirt);
    UnloadTexture(stone);
}
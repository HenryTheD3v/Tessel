#include <raylib.h>
#include "lib/gui.h"
#include "lib/player.h"
#include "lib/world.h"

static Texture2D crosshair;
static Texture2D grass;
static Texture2D dirt;
static Texture2D stone;
static Texture2D missing;
static Texture2D sand;

void InitGUI(void){
    crosshair = LoadTexture("assets/crosshair.png");
    grass = LoadTexture("assets/grasstop.png");
    dirt = LoadTexture("assets/dirt.png");
    stone = LoadTexture("assets/stone.png");
    missing = LoadTexture("assets/missing.png");
    sand = LoadTexture("assets/sand.png");
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
    DrawText("Tessel", 20, 20, 40, WHITE);
    int fps = GetFPS();
    DrawText(TextFormat("FPS: %d",fps), 20, 60, 40, WHITE);
    if(debug){
        DrawText("Debug Mode Enabled", 20, screenheight - 20, 10, WHITE);
        DrawText("Hold M for always grounded", 20, screenheight - 10, 10, WHITE);
        DrawText(TextFormat("X: %.1f Y: %.1f Z: %.1f",player.position.x, player.position.y + player.height / 2, player.position.z), 20, 100, 40, WHITE);
        DrawText(TextFormat("VX: %.1f VY: %.1f VZ: %.1f",player.velocity.x, player.velocity.y, player.velocity.z), 20, 140, 40, WHITE);
    }
    
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
    } else if(selectedBlock == 4){
        DrawTextureEx(sand,
        (Vector2){
            screenwidth - 20 - sand.height * 5,
            20,
        },
        0.0f,
        5.0f,
        (Color){255, 255, 255, 128});
    } else {
        DrawTextureEx(missing,
        (Vector2){
            screenwidth - 20 - missing.height * 5,
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
    UnloadTexture(missing);
    UnloadTexture(sand);
}
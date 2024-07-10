#include <iostream>
#include "raylib.h"

#define BACKGROUND_COLOR WHITE
#define MAP_SCALING_FACTOR 2.5f
#define MAP_SPAWNPOINT {-2600 * MAP_SCALING_FACTOR, -950 * MAP_SCALING_FACTOR}
#define MAP_ROTATION_ANGLE 0

const int window_width = 512;
const int window_height = 512;

int main() {
    InitWindow(window_width, window_height, "CLASHHH");

    Texture2D background = LoadTexture("assets\\my_map.png");

    SetTargetFPS(120);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        
        DrawTextureEx(background, MAP_SPAWNPOINT, MAP_ROTATION_ANGLE, MAP_SCALING_FACTOR, WHITE);

        // float dT = GetFrameTime();
    
        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
    return 0;
}
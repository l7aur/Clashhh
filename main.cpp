#include <iostream>
#include "raylib.h"
#include "raymath.h"

#define BACKGROUND_COLOR WHITE
#define MAP_SCALING_FACTOR 2.5f
#define MAP_SPAWNPOINT {-2600 * MAP_SCALING_FACTOR, -950 * MAP_SCALING_FACTOR}
#define MAP_ROTATION_ANGLE 0
#define STEP_SIZE 5.0f

const int window_width = 512;
const int window_height = 512;

int main() {
    InitWindow(window_width, window_height, "CLASHHH");

    Texture2D background = LoadTexture("assets\\my_map.png");
    Vector2 map_position = MAP_SPAWNPOINT;

    SetTargetFPS(120);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        
        DrawTextureEx(background, map_position, MAP_ROTATION_ANGLE, MAP_SCALING_FACTOR, WHITE);

        Vector2 direction = { 0.0f, 0.0f};
        if(IsKeyDown(KEY_A)) direction.x -= STEP_SIZE;
        if(IsKeyDown(KEY_D)) direction.x += STEP_SIZE;
        if(IsKeyDown(KEY_W)) direction.y -= STEP_SIZE;
        if(IsKeyDown(KEY_S)) direction.y += STEP_SIZE;
        if(Vector2Length(direction) != STEP_SIZE) direction = Vector2Scale(Vector2Normalize(direction), STEP_SIZE);

        map_position = Vector2Subtract(map_position, direction);

        // float dT = GetFrameTime();
    
        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
    return 0;
}
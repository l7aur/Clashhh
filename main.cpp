#include <iostream>
#include "raylib.h"
#include "raymath.h"

#define BACKGROUND_COLOR BLACK
#define MAP_SCALING_FACTOR 2.5f
#define CHARACTER_SCALING_FACTOR 2.0f
#define MAP_SPAWNPOINT {-2600 * MAP_SCALING_FACTOR, -950 * MAP_SCALING_FACTOR}
#define MAP_ROTATION_ANGLE 0.0f
#define STEP_SIZE 5.0f

const int window_width = 512;
const int window_height = 512;

void change_position(Vector2& map_position);

int main() {
    InitWindow(window_width, window_height, "CLASHHH");

    Texture2D background = LoadTexture("assets\\my_map.png");
    Vector2 map_position = MAP_SPAWNPOINT;

    Texture2D main_character = LoadTexture("assets\\characters\\main_character\\_Idle.png");
    Vector2 main_character_position = {(float)window_width / 2.0f - main_character.width / 20.0f, 
                                       (float)window_height / 2.0f - main_character.height / 2.0f};

    SetTargetFPS(120);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        
        DrawTextureEx(background, map_position, MAP_ROTATION_ANGLE, MAP_SCALING_FACTOR, WHITE);

        DrawTexturePro (main_character,
                        Rectangle {0.0f, 40.0f, (float)main_character.width / 10.0f, (float)main_character.height},
                        Rectangle {main_character_position.x, main_character_position.y, 
                                   CHARACTER_SCALING_FACTOR * (float)main_character.width / 10.0f, 
                                   CHARACTER_SCALING_FACTOR * (float)main_character.height},
                        Vector2 {}, 
                        0.0f,
                        WHITE);

        change_position(map_position);


        // float dT = GetFrameTime();
    
        EndDrawing();
    }

    UnloadTexture(background);
    CloseWindow();
    return 0;
}

void change_position(Vector2& map_position) {
    Vector2 direction = { 0.0f, 0.0f};
        if(IsKeyDown(KEY_A)) direction.x -= STEP_SIZE;
        if(IsKeyDown(KEY_D)) direction.x += STEP_SIZE;
        if(IsKeyDown(KEY_W)) direction.y -= STEP_SIZE;
        if(IsKeyDown(KEY_S)) direction.y += STEP_SIZE;
        if(Vector2Length(direction) > STEP_SIZE) direction = Vector2Scale(Vector2Normalize(direction), STEP_SIZE);
        map_position = Vector2Subtract(map_position, direction);
}
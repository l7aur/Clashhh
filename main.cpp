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

bool change_position(Vector2& map_position, int& facing_direction);

int main() {
    InitWindow(window_width, window_height, "CLASHHH");

    Texture2D background = LoadTexture("assets\\my_map.png");
    Vector2 map_position = MAP_SPAWNPOINT;

    Texture2D main_character_idle = LoadTexture("assets\\characters\\main_character\\_Idle.png");
    Texture2D main_character_running = LoadTexture("assets\\characters\\main_character\\_Run.png");
    Texture2D main_character = main_character_idle;
    Vector2 main_character_position = {(float)window_width / 2.0f - main_character_idle.width / 20.0f - 70.0f, 
                                       (float)window_height / 2.0f - main_character_idle.height / 2.0f};
    int facing_direction = 1;
    float running_time = 0.0f;
    const float update_time = 1.0f / 16.0f;
    int frame = 0;

    SetTargetFPS(120);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        float dT = GetFrameTime();
        
        //update running time of main character
        running_time += dT;

        //draw the background
        DrawTextureEx(background, map_position, MAP_ROTATION_ANGLE, MAP_SCALING_FACTOR, WHITE);

        //draw the main character
        DrawTexturePro (main_character,
                        Rectangle {frame * main_character.width / 10.0f, 40.0f, 
                           (float)(facing_direction * main_character.width) / 10.0f, (float)main_character.height},
                        Rectangle {main_character_position.x, main_character_position.y, 
                                   CHARACTER_SCALING_FACTOR * (float)main_character.width / 10.0f, 
                                   CHARACTER_SCALING_FACTOR * (float)main_character.height},
                        Vector2 {}, 
                        0.0f,
                        WHITE);

        //update the position of the main character and the spritesheet
        change_position(map_position, facing_direction) ? main_character = main_character_running : main_character =  main_character_idle;

        //change the frame of main character
        if(running_time >= update_time) {
            running_time = 0.0f;
            frame = (frame + 1) % 10;
        }
    
        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(main_character_idle);
    CloseWindow();
    return 0;
}

//update character position on map and the direction he is facing
//return true if the character is moving to update the spritesheet to the running state
//return false if the character is idling
bool change_position(Vector2& map_position, int &facing_direction) {
    Vector2 direction = { 0.0f, 0.0f};
    if(IsKeyDown(KEY_A)) direction.x -= STEP_SIZE;
    if(IsKeyDown(KEY_D)) direction.x += STEP_SIZE;
    if(IsKeyDown(KEY_W)) direction.y -= STEP_SIZE;
    if(IsKeyDown(KEY_S)) direction.y += STEP_SIZE;
    if(Vector2Length(direction) > STEP_SIZE) direction = Vector2Scale(Vector2Normalize(direction), STEP_SIZE);
    map_position = Vector2Subtract(map_position, direction);
    if(direction.x) (direction.x > 0) ? facing_direction = 1 : facing_direction = -1;
    if(Vector2Length(direction) > 0)
        return true;
    return false;
}
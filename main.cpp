#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

#define BACKGROUND_COLOR BLACK
#define MAP_SCALING_FACTOR 2.5f
#define MAP_ROTATION_ANGLE 0.0f

const int window_width = 512;
const int window_height = 512;

int main()
{
    InitWindow(window_width, window_height, "CLASHHH");

    Texture2D background = LoadTexture("assets\\my_map.png");
    Vector2 map_position = MAP_SPAWNPOINT;

    Character * main_character = new Character(MAP_SCALING_FACTOR, window_width, window_height);
    Prop * rock = new Prop(Vector2{0.0f, 0.0f}, LoadTexture("assets\\tiles\\rock.png"), 2.0f);

    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        map_position = Vector2Scale(main_character->getWorldPos(), -1.0f);

        // draw the background
        DrawTextureEx(background, map_position, MAP_ROTATION_ANGLE, MAP_SCALING_FACTOR, WHITE);
        rock->render(main_character->getWorldPos());

        main_character->tick(GetFrameTime());

        //check map bounds  
        if (main_character->getWorldPos().x < 0.0f ||
            main_character->getWorldPos().y < 0.0f ||
            main_character->getWorldPos().x + window_width > background.width * MAP_SCALING_FACTOR ||
            main_character->getWorldPos().y + window_height > background.height * MAP_SCALING_FACTOR) {
                main_character->undoMovement();
            }

        EndDrawing();
    }

    UnloadTexture(background);
    main_character->~Character();
    CloseWindow();
    return 0;
}
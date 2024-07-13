#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <vector>

#define BACKGROUND_COLOR BLACK
#define MAP_SCALING_FACTOR 2.5f
#define MAP_ROTATION_ANGLE 0.0f

const int window_width = 1024; // 512;
const int window_height = 512;

void setPropsOnTheMap(std::vector<Prop> &props);

int main()
{
    InitWindow(window_width, window_height, "CLASHHH");

    Texture2D background = LoadTexture("assets\\my_map.png");
    Vector2 map_position = spawnpoint;

    Character *main_character = new Character(MAP_SCALING_FACTOR, window_width, window_height, 5,
                                              LoadTexture("assets\\characters\\main_character\\_Idle.png"),
                                              LoadTexture("assets\\characters\\main_character\\_Run.png"));

    Enemy *enemy = new Enemy(MAP_SCALING_FACTOR, {10, 10}, main_character, 6, 3,
                             LoadTexture("assets\\characters\\orc\\Orc-Idle.png"),
                             LoadTexture("assets\\characters\\orc\\Orc-Walk.png"));

    std::vector<Prop> props;
    setPropsOnTheMap(props);

    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        map_position = Vector2Scale(main_character->getWorldPos(), -1.0f);

        // draw the background
        DrawTextureEx(background, map_position, MAP_ROTATION_ANGLE, MAP_SCALING_FACTOR, WHITE);

        // render props
        for (auto p : props)
        {
            p.render(main_character->getWorldPos());
            if (CheckCollisionRecs(p.getCollisionRec(main_character->getWorldPos()), main_character->getCollisionRec()))
                main_character->undoMovement();
        }

        main_character->tick(GetFrameTime());
        enemy->tick(GetFrameTime());

        std::cout << enemy->getWorldPos().x << ' ' << enemy->getWorldPos().y << ' ' << main_character->getWorldPos().x << ' ' << main_character->getWorldPos().y << '\n';

        // check map bounds
        if (main_character->getWorldPos().x < 0.0f ||
            main_character->getWorldPos().y < 0.0f ||
            main_character->getWorldPos().x + window_width > background.width * MAP_SCALING_FACTOR ||
            main_character->getWorldPos().y + window_height > background.height * MAP_SCALING_FACTOR)
        {
            main_character->undoMovement();
        }

        // collision boxes debug
        /*DrawRectangle(props[0].getCollisionRec(main_character->getWorldPos()).x,
                    props[0].getCollisionRec(main_character->getWorldPos()).y,
                    props[0].getCollisionRec(main_character->getWorldPos()).width,
                    props[0].getCollisionRec(main_character->getWorldPos()).height,
                    BLACK
                    );
        DrawRectangle(props[1].getCollisionRec(main_character->getWorldPos()).x,
                    props[1].getCollisionRec(main_character->getWorldPos()).y,
                    props[1].getCollisionRec(main_character->getWorldPos()).width,
                    props[1].getCollisionRec(main_character->getWorldPos()).height,
                    BLACK
                    );
        DrawRectangle(main_character->getCollisionRec().x,
                    main_character->getCollisionRec().y,
                    main_character->getCollisionRec().width,
                    main_character->getCollisionRec().height,
                    GREEN
                    );*/

        EndDrawing();
    }

    UnloadTexture(background);

    CloseWindow();
    return 0;
}

void setPropsOnTheMap(std::vector<Prop> &props)
{
    props.push_back(
        Prop(MAP_SCALING_FACTOR, Vector2{2600.0f, 800.0f}, LoadTexture("assets\\props\\rock1.png"), 5.0f));
    props.push_back(
        Prop(MAP_SCALING_FACTOR, Vector2{2800.0f, 800.0f}, LoadTexture("assets\\props\\rock2.png"), 3.0f));
}

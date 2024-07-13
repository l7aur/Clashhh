#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <vector>

const Color background_color = BLACK;
const float map_scaling_factor = 2.5f;
const float map_rotation_angle = 0.0f;
const int window_width = 1024;
const int window_height = 512;
const float main_character_speed = 3.0f;
const int number_of_frames_orc = 6;
const int number_of_frames_soldier = 6;

void setPropsOnTheMap(std::vector<Prop *> &props);
void setOrcsOnTheMap(Character *main_character, std::vector<Enemy *> &orcs);
void setSoldiersOnTheMap(Character *main_character, std::vector<Enemy *> &soldiers);

int main()
{
    InitWindow(window_width, window_height, "CLASHHH");

    Texture2D background = LoadTexture("assets\\my_map.png");
    Vector2 map_position = spawnpoint;

    std::vector<Enemy *> orcs;
    std::vector<Enemy *> soldiers;
    std::vector<Prop *> props;

    Character *main_character = new Character(map_scaling_factor, window_width, window_height, main_character_speed,
                                              LoadTexture("assets\\characters\\main_character\\_Idle.png"),
                                              LoadTexture("assets\\characters\\main_character\\_Run.png"));

    setPropsOnTheMap(props);
    setOrcsOnTheMap(main_character, orcs);
    setSoldiersOnTheMap(main_character, soldiers);

    SetTargetFPS(120);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(background_color);
        map_position = Vector2Scale(main_character->getWorldPos(), -1.0f);

        // draw the background
        DrawTextureEx(background, map_position, map_rotation_angle, map_scaling_factor, WHITE);

        // render props
        for (auto p : props)
        {
            p->render(main_character->getWorldPos());
            if (CheckCollisionRecs(p->getCollisionRec(main_character->getWorldPos()), main_character->getCollisionRec()))
                main_character->undoMovement();
        }

        // update characters
        float deltaTime = GetFrameTime();
        main_character->tick(deltaTime);
        for (Enemy *orc : orcs)
            orc->tick(deltaTime);
        for (Enemy *soldier : soldiers)
            soldier->tick(deltaTime);

        // check map bounds
        if (main_character->getWorldPos().x < 0.0f ||
            main_character->getWorldPos().y < 0.0f ||
            main_character->getWorldPos().x + window_width > background.width * map_scaling_factor ||
            main_character->getWorldPos().y + window_height > background.height * map_scaling_factor)
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

void setOrcsOnTheMap(Character *main_character, std::vector<Enemy *> &orcs)
{
    const float patrolledArea = 250.f;
    Texture2D idle = LoadTexture("assets\\characters\\orc\\Orc-Idle.png");
    Texture2D running = LoadTexture("assets\\characters\\orc\\Orc-Walk.png");
    orcs.push_back(new Enemy(map_scaling_factor, {2500 * map_scaling_factor, 1000 * map_scaling_factor}, main_character, number_of_frames_orc, /*speed*/ 1.0f, patrolledArea, idle, running));
}

void setSoldiersOnTheMap(Character *main_character, std::vector<Enemy *> &soldiers)
{
    const float patrolledArea = 400.f;
    Texture2D idle = LoadTexture("assets\\characters\\soldier\\Soldier-Idle.png");
    Texture2D running = LoadTexture("assets\\characters\\soldier\\Soldier-Walk.png");
    soldiers.push_back(new Enemy(map_scaling_factor, {3000 * map_scaling_factor, 1500 * map_scaling_factor}, main_character, number_of_frames_soldier, /*speed*/ 1.5f, patrolledArea, idle, running));
}

void setPropsOnTheMap(std::vector<Prop *> &props)
{
    props.push_back(new Prop(map_scaling_factor, Vector2{2600.0f, 800.0f}, LoadTexture("assets\\props\\rock1.png"), 5.0f));
    props.push_back(new Prop(map_scaling_factor, Vector2{2800.0f, 800.0f}, LoadTexture("assets\\props\\rock2.png"), 3.0f));
    props.push_back(new Prop(map_scaling_factor, Vector2{3000.0f, 800.0f}, LoadTexture("assets\\props\\chest.png"), 3.0f));
}

#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <vector>

const float map_scaling_factor = 2.5f;

void setPropsOnTheMap(std::vector<Prop *> &props);
void setOrcsOnTheMap(Character *main_character, std::vector<Enemy *> &orcs);
void setSoldiersOnTheMap(Character *main_character, std::vector<Enemy *> &soldiers);

int main()
{
    const float main_character_speed = 3.0f;
    const float map_rotation_angle = 0.0f;
    const int window_width = 1024;
    const int window_height = 512;
    float timer = 2.0f;
    const Color background_color = BLACK;
    bool stop_handling_events = false;
    std::vector<Enemy *> orcs;
    std::vector<Enemy *> soldiers;
    std::vector<Prop *> props;

    InitWindow(window_width, window_height, "CLASHHH");

    Texture2D background = LoadTexture("assets\\my_map.png");
    Vector2 map_position = spawnpoint;

    Character *main_character = new Character(map_scaling_factor, window_width, window_height, main_character_speed,
                                              LoadTexture("assets\\characters\\main_character\\_Idle.png"),
                                              LoadTexture("assets\\characters\\main_character\\_Run.png"),
                                              LoadTexture("assets\\characters\\main_character\\_Attack2.png"));

    setPropsOnTheMap(props);
    setOrcsOnTheMap(main_character, orcs);
    // setSoldiersOnTheMap(main_character, soldiers);

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
            for (auto o : orcs)
                if (CheckCollisionRecs(p->getCollisionRec(main_character->getWorldPos()), o->getCollisionRec()))
                    o->undoMovement();
            for (auto s : soldiers)
                if (CheckCollisionRecs(p->getCollisionRec(main_character->getWorldPos()), s->getCollisionRec()))
                    s->undoMovement();
        }

        // update characters
        float deltaTime = GetFrameTime();
        main_character->tick(deltaTime);
        if (!stop_handling_events)
        {
            for (Enemy *orc : orcs)
                orc->tick(deltaTime);
            for (Enemy *soldier : soldiers)
                soldier->tick(deltaTime);
        }
        else
            main_character->undoMovement();

        // check map bounds
        if (main_character->getWorldPos().x < 0.0f ||
            main_character->getWorldPos().y < 0.0f ||
            main_character->getWorldPos().x + window_width > background.width * map_scaling_factor ||
            main_character->getWorldPos().y + window_height > background.height * map_scaling_factor)
        {
            main_character->undoMovement();
        }

        if (!main_character->getAlive())
        {
            DrawText("GAME ENDED!", 370, 170, 40, BLACK);
            stop_handling_events = true;
            timer -= deltaTime;
        }

        EndDrawing();
        if (timer <= 0)
            break;
    }

    UnloadTexture(background);

    CloseWindow();
    return 0;
}

void setOrcsOnTheMap(Character *main_character, std::vector<Enemy *> &orcs)
{
    const int number_of_frames_orc = 6;
    const float patrolledArea = 250.f;
    const float orcSpeed = 1.0f;
    const float range = 20.0f;
    const float orcDamage = 5.0f;
    Texture2D idle = LoadTexture("assets\\characters\\orc\\Orc-Idle.png");
    Texture2D running = LoadTexture("assets\\characters\\orc\\Orc-Walk.png");
    Texture2D attacking = LoadTexture("assets\\characters\\orc\\Orc-Attack01.png");
    Texture2D dying = LoadTexture("assets\\characters\\orc\\Orc-Death.png");
    // spawn_island
    for (int i = 0; i < 30; i++)
    { // above spawnpoint
        float xCoord = static_cast<float>(rand() % 880 + 2700);
        float yCoord = static_cast<float>(rand() % 760 + 180);
        orcs.push_back(new Enemy(map_scaling_factor, {xCoord, yCoord}, main_character, number_of_frames_orc, orcSpeed, patrolledArea, range, orcDamage, idle, running, attacking, dying));
    }
    for (int i = 0; i < 20; i++)
    { // below spawnpoint
        float xCoord = static_cast<float>(rand() % 880 + 2700);
        float yCoord = static_cast<float>(rand() % 360 + 1280);
        orcs.push_back(new Enemy(map_scaling_factor, {xCoord, yCoord}, main_character, number_of_frames_orc, orcSpeed, patrolledArea, range, orcDamage, idle, running, attacking, dying));

    }
    for (int i = 0; i < 20; i++)
    { // right of spawnpoint
        float xCoord = static_cast<float>(rand() % 700 + 2950);
        float yCoord = static_cast<float>(rand() % 700 + 800);
        orcs.push_back(new Enemy(map_scaling_factor, {xCoord, yCoord}, main_character, number_of_frames_orc, orcSpeed, patrolledArea, range, orcDamage, idle, running, attacking, dying));

    }
}

void setSoldiersOnTheMap(Character *main_character, std::vector<Enemy *> &soldiers)
{
    const int number_of_frames_soldier = 6;
    const float patrolledArea = 400.f;
    const float soldierSpeed = 1.6f;
    const float range = 20.0f;
    const float soldierDamage = 15.0f;
    Texture2D idle = LoadTexture("assets\\characters\\soldier\\Soldier-Idle.png");
    Texture2D running = LoadTexture("assets\\characters\\soldier\\Soldier-Walk.png");
    Texture2D attacking = LoadTexture("assets\\characters\\soldier\\Soldier-Attack01.png");
    Texture2D dying = LoadTexture("assets\\characters\\soldier\\Soldier-Death.png");
    // middle island
    for (int i = 0; i < 30; i++)
    { // leftmost area
        float xCoord = static_cast<float>(rand() % 730 + 230);
        float yCoord = static_cast<float>(rand() % 665 + 190);
        soldiers.push_back(new Enemy(map_scaling_factor, {xCoord, yCoord}, main_character, number_of_frames_soldier, soldierSpeed, patrolledArea, range, soldierDamage, idle, running, attacking, dying));
    }
    for (int i = 0; i < 30; i++)
    { // central area
        float xCoord = static_cast<float>(rand() % 950 + 1100);
        float yCoord = static_cast<float>(rand() % 590 + 425);
        soldiers.push_back(new Enemy(map_scaling_factor, {xCoord, yCoord}, main_character, number_of_frames_soldier, soldierSpeed, patrolledArea, range, soldierDamage, idle, running, attacking, dying));
    }
    for (int i = 0; i < 30; i++)
    { // upperright lobe area
        float xCoord = static_cast<float>(rand() % 480 + 1480);
        float yCoord = static_cast<float>(rand() % 240 + 200);        
        soldiers.push_back(new Enemy(map_scaling_factor, {xCoord, yCoord}, main_character, number_of_frames_soldier, soldierSpeed, patrolledArea, range, soldierDamage, idle, running, attacking, dying));

    }
    for (int i = 0; i < 30; i++)
    { // lowerright lobe1 area
        float xCoord = static_cast<float>(rand() % 530 + 1580);
        float yCoord = static_cast<float>(rand() % 250 + 1000);
        soldiers.push_back(new Enemy(map_scaling_factor, {xCoord, yCoord}, main_character, number_of_frames_soldier, soldierSpeed, patrolledArea, range, soldierDamage, idle, running, attacking, dying));
    }
    for (int i = 0; i < 30; i++)
    { // lowerright lobe2 area
        float xCoord = static_cast<float>(rand() % 450 + 1830);
        float yCoord = static_cast<float>(rand() % 450 + 1350);
        soldiers.push_back(new Enemy(map_scaling_factor, {xCoord, yCoord}, main_character, number_of_frames_soldier, soldierSpeed, patrolledArea, range, soldierDamage, idle, running, attacking, dying));
    }
}

void setPropsOnTheMap(std::vector<Prop *> &props)
{
    props.push_back(new Prop(map_scaling_factor, Vector2{2600.0f, 800.0f}, LoadTexture("assets\\props\\rock1.png"), 5.0f));
    props.push_back(new Prop(map_scaling_factor, Vector2{2800.0f, 800.0f}, LoadTexture("assets\\props\\rock2.png"), 3.0f));
    props.push_back(new Prop(map_scaling_factor, Vector2{3000.0f, 800.0f}, LoadTexture("assets\\props\\chest.png"), 3.0f));
}

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPosition; }
    void undoMovement();
    Rectangle getCollisionRec();
    ~BaseCharacter();

protected:
    Vector2 computeDirection();

    Texture2D idle{LoadTexture("assets\\characters\\main_character\\_Idle.png")};
    Texture2D running{LoadTexture("assets\\characters\\main_character\\_Run.png")};
    Texture2D texture = idle;
    Vector2 screenPosition = {};
    Vector2 worldPosition = {2500, 1000};
    Vector2 pastWorldPosition{};
    int facingDirection{1};
    float runningTime{0.0f};
    int frame{0};
    const float updateTime{1.0f / 16.0f};
    const float speed = 5.0f;
    int width{};
    int height{};
    int numberOfFrames{10};
    const float scale{2.0f};

private:

};

#endif
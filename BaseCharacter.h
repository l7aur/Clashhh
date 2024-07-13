#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

const Vector2 spawnpoint = {2500, 1000};

class BaseCharacter
{
public:
    inline Vector2 getWorldPos() { return worldPosition; }
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime); 
    virtual Vector2 computeDirection();
    virtual Vector2 getScreenPosition() = 0; //pure virtual function => abstract class
    ~BaseCharacter();
protected:

    Texture2D idle{};
    Texture2D running{};
    Texture2D texture{};
    Vector2 worldPosition{spawnpoint};
    Vector2 pastWorldPosition{};
    int facingDirection{1};
    float runningTime{0.0f};
    int frame{0};
    const float updateTime{1.0f / 16.0f};
    int width{};
    int height{};
    int numberOfFrames{10};
    const float scale{2.0f};
    float stepSize{0};

private:

};

#endif
#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    this->worldPosition = this->pastWorldPosition;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle {
        this->screenPosition.x + 45 * this->scale, this->screenPosition.y,
        30 * this->scale, this->height * this->scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    // change the frame of character
    this->runningTime += deltaTime;
    if (this->runningTime >= this->updateTime)
    {
        this->runningTime = 0.0f;
        this->frame = (this->frame + 1) % numberOfFrames;
    }

    // draw the character
    DrawTexturePro(texture,
                   Rectangle{static_cast<float>(frame * width), static_cast<float>(height), static_cast<float>(facingDirection * width), static_cast<float>(height)},
                   Rectangle{this->screenPosition.x, this->screenPosition.y,
                             this->scale * static_cast<float>(width), this->scale * static_cast<float>(height)},
                   Vector2{},
                   0.0f,
                   WHITE);
}

Vector2 BaseCharacter::computeDirection()
{
    Vector2 direction = {0.0f, 0.0f};
    if (IsKeyDown(KEY_A))
        direction.x -= 5;
    if (IsKeyDown(KEY_D))
        direction.x += 5;
    if (IsKeyDown(KEY_W))
        direction.y -= 5;
    if (IsKeyDown(KEY_S))
        direction.y += 5;
    return direction;
}

BaseCharacter::~BaseCharacter()
{
}
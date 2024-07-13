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
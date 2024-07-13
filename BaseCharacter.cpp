#include "BaseCharacter.h"
#include "raymath.h"

void BaseCharacter::undoMovement()
{
    this->worldPosition = this->pastWorldPosition;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle {
        this->getScreenPosition().x + 45 * this->scale, this->getScreenPosition().y,
        30 * this->scale, this->height * this->scale
    };
}

void BaseCharacter::tick(float deltaTime)
{
    Vector2 direction = computeDirection();

    this->pastWorldPosition = this->worldPosition;
    this->worldPosition = Vector2Add(this->worldPosition, direction);
    if (direction.x)
        (direction.x > 0) ? this->facingDirection = 1 : this->facingDirection = -1;
    (Vector2Length(direction)) ? this->texture = this->running : this->texture = this->idle;

    worldPosition = Vector2Add(worldPosition, direction);

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
                   Rectangle{this->getScreenPosition().x, this->getScreenPosition().y,
                             this->scale * static_cast<float>(width), this->scale * static_cast<float>(height)},
                   Vector2{},
                   0.0f,
                   WHITE);
}

Vector2 BaseCharacter::computeDirection()
{
    Vector2 direction = {0.0f, 0.0f};
    if (IsKeyDown(KEY_A))
        direction.x -= stepSize;
    if (IsKeyDown(KEY_D))
        direction.x += stepSize;
    if (IsKeyDown(KEY_W))
        direction.y -= stepSize;
    if (IsKeyDown(KEY_S))
        direction.y += stepSize;
    if (Vector2Length(direction) > stepSize)
        direction = Vector2Scale(Vector2Normalize(direction), stepSize);
    return direction;
}

BaseCharacter::~BaseCharacter()
{
}
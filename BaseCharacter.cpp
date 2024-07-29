#include "BaseCharacter.h"
#include "raymath.h"
void BaseCharacter::undoMovement()
{
    this->worldPosition = this->pastWorldPosition;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        this->getScreenPosition().x + 45 * this->scale, this->getScreenPosition().y,
        30 * this->scale, this->height * this->scale};
}

void BaseCharacter::tick(float deltaTime)
{
    Vector2 direction = computeDirection();
    this->pastWorldPosition = this->worldPosition;
    this->worldPosition = Vector2Add(this->worldPosition, direction);
    if (direction.x)
        (direction.x > 0) ? this->facingDirection = 1 : this->facingDirection = -1;
    if (!attackingAnimation && this->getState() != STATE::DEAD)
    {
        if (Vector2Length(direction))
        {
            this->texture = this->running;
            this->setState(STATE::RUNNING);
        }
        else
        {
            this->texture = this->idle;
            this->setState(STATE::IDLE);
        }
    }

    worldPosition = Vector2Add(worldPosition, direction);

    // change the frame of character
    this->runningTime += deltaTime;
    if (this->runningTime >= this->updateTime)
    {
        this->runningTime = 0.0f;
        if (this->getState() == STATE::DEAD)
            this->frame = (this->frame == numberOfDeathFrames - 1) ? numberOfDeathFrames - 1 : this->frame + 1;
        else
        {
            if (this->frame == 5 && attackingAnimation)
                attackingAnimation = false;
            this->frame = (this->frame + 1) % numberOfFrames;
        }
    }
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
    UnloadTexture(idle);
    UnloadTexture(running);
    UnloadTexture(texture);
}
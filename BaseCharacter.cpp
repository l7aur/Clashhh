#include "BaseCharacter.h"
#include "raymath.h"

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        this->getScreenPosition().x + 45 * this->scale, this->getScreenPosition().y,
        30 * this->scale, this->height * this->scale};
}

void BaseCharacter::tick(const float deltaTime)
{
    this->runningTime += deltaTime;
    this->setHealthBar();
    Vector2 direction = computeDirection();
    this->pastWorldPosition = this->worldPosition;
    this->worldPosition = Vector2Add(this->worldPosition, direction);
    if (direction.x)
        (direction.x > 0) ? this->facingDirection = 1 : this->facingDirection = -1;
    if (this->getState() != STATE::ATTACKING && this->getState() != STATE::HURT && this->getState() != STATE::DEAD)//attackingAnimation == false && this->getState() != STATE::DEAD && this->getState() != STATE::HURT)
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
    if (this->runningTime >= this->updateTime)
    {
        this->runningTime = 0.0f;
        if (this->getState() == STATE::DEAD)
            this->frame = (this->frame == numberOfDeathFrames - 1) ? numberOfDeathFrames - 1 : this->frame + 1;
        else if (this->getState() == STATE::HURT)
        {
            if (this->frame == 3)
                this->setState(STATE::IDLE);
            frame = (this->frame + 1) % 4;
        }
        else
        {
            if (this->frame == 5 && this->getState() == STATE::ATTACKING)
                this->setState(STATE::IDLE);
            this->frame = (this->frame + 1) % numberOfFrames;
        }
    }
    /* DEBUG */ // draw hitboxes
    // DrawRectangle(getCollisionRec().x, getCollisionRec().y, getCollisionRec().width, getCollisionRec().height, RED);
    /* DEBUG */ // draw attackboxes
    // DrawRectangle(getAttackArea().x, getAttackArea().y, getAttackArea().width, getAttackArea().height, GREEN);
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

void BaseCharacter::setHealthBar()
{
    Rectangle boundingBox = this->getCollisionRec();
    float scale = this->getHealth() / this->getMaximumHealth();
    if (this->getHealth() > 0)
    {
        DrawRectangle(boundingBox.x, boundingBox.y - 20, boundingBox.width, 15, RED);
        DrawRectangle(boundingBox.x, boundingBox.y - 20, boundingBox.width * scale, 15, GREEN);
    }
}
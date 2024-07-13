#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(const float map_scaling_factor, Vector2 wPosition, Character *target, int numberOfFrames, const float stepSize, const float patrolledArea, Texture2D idle_texture, Texture2D running_texture) : target(target), patrolledArea(patrolledArea)
{
    this->idle = idle_texture, this->running = running_texture;
    this->stepSize = stepSize;
    this->numberOfFrames = numberOfFrames;
    this->width = idle_texture.width / numberOfFrames;
    this->height = idle_texture.height;
    this->worldPosition = wPosition;
}

void Enemy::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::computeDirection()
{
    Vector2 direction = Vector2Subtract(this->target->getScreenPosition(), this->getScreenPosition());
    float magnitude = Vector2Length(direction);
    if (magnitude > patrolledArea)
        return {0, 0};
    if (magnitude < 10.0f)
        return {0, 0};
    return Vector2Scale(Vector2Normalize(direction), this->stepSize);
}

Vector2 Enemy::getScreenPosition()
{
    return Vector2Subtract(this->worldPosition, this->target->getWorldPos());
}

Enemy::~Enemy()
{
    UnloadTexture(idle);
    UnloadTexture(running);
    UnloadTexture(texture);
}
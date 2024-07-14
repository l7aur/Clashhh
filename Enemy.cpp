#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(const float map_scaling_factor, Vector2 wPosition, Character *target, int numberOfFrames, const float stepSize, const float patrolledArea, const float range, Texture2D idle_texture, Texture2D running_texture)
    : target(target), patrolledArea(patrolledArea),
      correctionFactor(Vector2Scale({static_cast<float>(-target->getFigureWidth()), static_cast<float>(target->getFigureHeight())}, 0.5f * map_scaling_factor)), range(range)
{
    this->idle = idle_texture, this->running = running_texture;
    this->stepSize = stepSize;
    this->numberOfFrames = numberOfFrames;
    this->width = idle_texture.width / numberOfFrames;
    this->height = idle_texture.height;
    this->worldPosition = Vector2Scale(wPosition, map_scaling_factor);
}

void Enemy::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::computeDirection()
{
    // to the left of the character
    Vector2 direction1 = Vector2Subtract(this->target->getScreenPosition(), this->getScreenPosition());
    direction1.y -= correctionFactor.y;
    // to the right of the character
    Vector2 direction2 = Vector2Subtract(Vector2Subtract(this->target->getScreenPosition(), this->getScreenPosition()), this->correctionFactor);
    Vector2 direction = (Vector2Length(direction1) > Vector2Length(direction2)) ? direction2 : direction1;
    float magnitude = Vector2Length(direction);
    if (magnitude > patrolledArea)
        return {0, 0};
    if (magnitude < 10.0f) //remove flickering when to the target
        return {0, 0};
    if (magnitude < range)
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
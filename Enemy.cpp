#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(const float map_scaling_factor, Vector2 position, Texture2D idle_texture, Texture2D running_texture, int numberOfFrames, Character * target)
{
    this->idle = idle_texture;
    this->running = running_texture;
    this->texture = this->idle;
    this->numberOfFrames = numberOfFrames;
    this->width = idle_texture.width / numberOfFrames;
    this->height = idle_texture.height;
    this->worldPosition = {2500 * map_scaling_factor, 1000 * map_scaling_factor};
    this->target = target;
}

void Enemy::tick(float deltaTime) {
    Vector2 targetPosition = this->target->getWorldPos();
    targetPosition.x--;
    targetPosition.y -= 10;
    this->screenPosition = Vector2Subtract(this->worldPosition, targetPosition);
    BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::computeDirection() {
    return Vector2Scale(Vector2Normalize(Vector2Subtract(this->target->getScreenPosition(), this->screenPosition)), this->speed - 3.0f);
}


Enemy::~Enemy() {
    UnloadTexture(idle);
    UnloadTexture(running);
    UnloadTexture(texture);
}
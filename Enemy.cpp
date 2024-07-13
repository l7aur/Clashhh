#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(const float map_scaling_factor, Vector2 position, Texture2D idle_texture, Texture2D running_texture, int numberOfFrames)
{
    this->idle = idle_texture;
    this->running = running_texture;
    this->texture = this->idle;
    this->screenPosition = position;
    this->numberOfFrames = numberOfFrames;
    this->width = idle_texture.width / numberOfFrames;
    this->height = idle_texture.height;
    this->worldPosition = {2500 * map_scaling_factor, 1000 * map_scaling_factor};
}

void Enemy::tick(float deltaTime) {
    BaseCharacter::tick(deltaTime);
}

Enemy::~Enemy() {
    UnloadTexture(idle);
    UnloadTexture(running);
    UnloadTexture(texture);
}
#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(const float map_scaling_factor, Vector2 position, Texture2D idle_texture, Texture2D running_texture, int numberOfFrames)
{
    this->idle = idle_texture;
    this->running = running_texture;
    this->screenPosition = position;
    this->numberOfFrames = numberOfFrames;
    this->width = idle_texture.width / numberOfFrames;
    this->height = idle_texture.height;
    this->worldPosition = {2500 * map_scaling_factor, 1000 * map_scaling_factor};
}

void Enemy::tick(float deltaTime) {
    Vector2 direction = computeDirection();

    if (Vector2Length(direction) > STEP_SIZE_E)
        direction = Vector2Scale(Vector2Normalize(direction), STEP_SIZE_E);
    this->pastWorldPosition = this->worldPosition;
    this->worldPosition = Vector2Add(this->worldPosition, direction);
    if (direction.x)
        (direction.x > 0) ? this->facingDirection = 1 : this->facingDirection = -1;
    (Vector2Length(direction)) ? this->texture = this->running : this->texture = this->idle;

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

Enemy::~Enemy() {
    UnloadTexture(idle);
    UnloadTexture(running);
    UnloadTexture(texture);
}
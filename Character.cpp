#include "Character.h"
#include "raymath.h"

Character::Character(const float map_scaling_factor, const int windowWidth, const int windowHeight, const float stepSize, Texture2D idle_texture, Texture2D running_texture) : windowWidth(windowWidth), windowHeight(windowHeight)
{
    this->idle = idle_texture, this->running = running_texture, this->texture = idle;
    this->stepSize = stepSize;
    this->width = this->texture.width / numberOfFrames;
    this->height = 40;
    this->worldPosition = Vector2Scale(this->worldPosition, map_scaling_factor);
}

Character::~Character()
{
    UnloadTexture(this->idle);
    UnloadTexture(this->running);
    UnloadTexture(this->texture);
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);
}

inline Vector2 Character::getScreenPosition()
{
    return {static_cast<float>(windowWidth) / 2.0f - this->width / 2.0f - 65.0f,
            static_cast<float>(windowHeight) / 2.0f - this->height / 2.0f - 25.0f};
}

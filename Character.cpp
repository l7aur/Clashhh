#include "Character.h"
#include "raymath.h"

Character::Character(const float map_scaling_factor, const int windowWidth, const int windowHeight)
{
    this->width = this->texture.width / numberOfFrames;
    this->height = 40;
    this->worldPosition = Vector2Scale(this->worldPosition, map_scaling_factor);
    this->screenPosition = {static_cast<float>(windowWidth) / 2.0f - this->width / 2.0f - 65.0f,
                            static_cast<float>(windowHeight) / 2.0f - this->height / 2.0f - 25.0f};
}

Character::~Character() {
    UnloadTexture(this->idle);
    UnloadTexture(this->running);
    UnloadTexture(this->texture);
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);
}
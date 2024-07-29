#include "Character.h"
#include "raymath.h"
#include <iostream>

Character::Character(const float map_scaling_factor, const int windowWidth, const int windowHeight, const float stepSize, Texture2D idle_texture, Texture2D running_texture, Texture2D attacking_texture)
    : windowWidth(windowWidth),
      windowHeight(windowHeight)
{
    this->setDamage(50.0f);
    this->setHealth(100.0f);
    this->numberOfDeathFrames = this->numberOfFrames = 10;
    this->idle = idle_texture, this->running = running_texture, this->texture = idle, this->attacking = attacking_texture;
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
    // draw the character
    if (!attackingAnimation && IsKeyPressed(KEY_SPACE))
    {
        texture = attacking;
        attackingAnimation = true;
        this->setState(STATE::ATTACKING);
        this->frame = 0;
    }

    if (this->getHealth() <= 0 && this->getState() != STATE::DEAD)
    {
        texture = death;
        this->setState(STATE::DEAD);
        this->frame = 0;
    }
    DrawTexturePro(texture,
                   Rectangle{static_cast<float>(frame * width), static_cast<float>(height), static_cast<float>(facingDirection * width), static_cast<float>(height)},
                   Rectangle{this->getScreenPosition().x, this->getScreenPosition().y,
                             this->scale * static_cast<float>(width), this->scale * static_cast<float>(height)},
                   Vector2{},
                   0.0f,
                   WHITE);
}

Vector2 Character::computeDirection()
{
    if (attackingAnimation)
        return {0, 0};
    return BaseCharacter::computeDirection();
}

inline Vector2 Character::getScreenPosition()
{
    return {static_cast<float>(windowWidth) / 2.0f - this->width / 2.0f - 65.0f,
            static_cast<float>(windowHeight) / 2.0f - this->height / 2.0f - 25.0f};
}

Rectangle Character::getAttackArea()
{
    if (!attackingAnimation || this->getState() == STATE::DEAD)
        return Rectangle();
    if (this->frame == 0 || this->frame == 5)
        return Rectangle();
    float xCoord = (facingDirection == 1) ? this->getScreenPosition().x + 130 : this->getScreenPosition().x + this->width / 2 - 20;
    return Rectangle{xCoord, this->getScreenPosition().y - 10, 70.0f, 100.0f};
}

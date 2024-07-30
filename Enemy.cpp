#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(const float map_scaling_factor, Vector2 wPosition, Character *target, int numberOfFrames, const float stepSize, const float patrollableArea, const float range, const float damage, const float enemy_health, Texture2D idle_texture, Texture2D running_texture, Texture2D attacking_texture, Texture2D hurt_texure, Texture2D death_texture)
    : target(target), patrolledArea(patrollableArea),
      correctionFactor(Vector2Scale({static_cast<float>(-target->getFigureWidth()), static_cast<float>(target->getFigureHeight())}, 0.5f * map_scaling_factor)), range(range)
{
    this->setDamage(damage);
    this->setHealth(enemy_health);
    this->idle = idle_texture, this->running = running_texture, this->attacking = attacking_texture;
    this->death = death_texture, this->hurt = hurt_texure, this->texture = idle;
    this->stepSize = stepSize;
    this->setDamage(damage);
    this->numberOfFrames = numberOfFrames;
    this->width = idle_texture.width / numberOfFrames;
    this->height = idle_texture.height;
    this->worldPosition = Vector2Scale(wPosition, map_scaling_factor);
    this->facingDirection = (rand() % 2) ? 1 : -1;
    this->numberOfDeathFrames = 4;
}

void Enemy::tick(const float deltaTime)
{
    BaseCharacter::tick(deltaTime);
    bool enemyCanAttack = CheckCollisionRecs(this->target->getCollisionRec(), this->getAttackArea());

    if (enemyCanAttack && this->getState() != STATE::DEAD && this->getState() != STATE::HURT)
    {
        if (this->getState() != STATE::ATTACKING)
        {
            this->texture = attacking;
            this->setState(STATE::ATTACKING);
            this->frame = 0;
        }
        if (this->frame >= 4)
            this->target->takeDamage(this->getDamage() * deltaTime);
    }

    // main character damages the enemies
    if (this->getState() != STATE::DEAD)
    {
        if (CheckCollisionRecs(this->getCollisionRec(), this->target->getAttackArea()) && this->target->getState() == STATE::ATTACKING)
        {
            this->takeDamage(deltaTime * this->target->getDamage());
            this->setState(STATE::HURT);
            this->texture = hurt;
            this->frame = 1;
        }
        if (this->getHealth() <= 0)
        {
            this->setState(STATE::DEAD);
            this->texture = death;
            this->frame = 0;
        }
    }
    else
        this->deathTimer += deltaTime;

    // draw the character
    DrawTexturePro(texture,
                   Rectangle{static_cast<float>(frame * width), static_cast<float>(height), static_cast<float>(facingDirection * width), static_cast<float>(height)},
                   Rectangle{this->getScreenPosition().x, this->getScreenPosition().y,
                             this->scale * static_cast<float>(width), this->scale * static_cast<float>(height)},
                   Vector2{},
                   0.0f,
                   WHITE);
}

Rectangle Enemy::getCollisionRec()
{
    return Rectangle{this->getScreenPosition().x + 88, this->getScreenPosition().y + 80, 25, 40};
}

Vector2 Enemy::computeDirection()
{
    if (this->getState() == STATE::DEAD)
        return {};
    // to the left of the character
    Vector2 direction1 = Vector2Subtract(this->target->getScreenPosition(), this->getScreenPosition());
    direction1.y -= correctionFactor.y;
    // to the right of the character
    Vector2 direction2 = Vector2Subtract(Vector2Subtract(this->target->getScreenPosition(), this->getScreenPosition()), this->correctionFactor);
    Vector2 direction = (Vector2Length(direction1) > Vector2Length(direction2)) ? direction2 : direction1;
    float magnitude = Vector2Length(direction);
    if (magnitude > patrolledArea)
        return {0, 0};
    if (magnitude < 10.0f) // remove flickering when next to the target
        return {0, 0};
    if (magnitude < range)
        return {0, 0};
    return Vector2Scale(Vector2Normalize(direction), this->stepSize);
}

Vector2 Enemy::getScreenPosition()
{
    return Vector2Subtract(this->worldPosition, this->target->getWorldPos());
}

Rectangle Enemy::getAttackArea()
{
    float xCoord = (facingDirection == 1) ? this->getScreenPosition().x + 110 : this->getScreenPosition().x + this->width / 2 + 10;
    return Rectangle{xCoord, this->getScreenPosition().y + 75, 30.0f, 50.0f};
}

Enemy::~Enemy()
{
    UnloadTexture(idle);
    UnloadTexture(running);
    UnloadTexture(attacking);
    UnloadTexture(hurt);
    UnloadTexture(death);
}
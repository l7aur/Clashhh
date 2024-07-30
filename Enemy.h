#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(const float map_scaling_factor, Vector2 wPosition, Character *target, int numberOfFrames, const float stepSize, const float patrollableArea, const float range, const float damage, const float enemy_health, Texture2D idle_texture, Texture2D running_texture, Texture2D attacking_texture, Texture2D death_texture);
    virtual void tick(float deltaTime) override;
    virtual Rectangle getCollisionRec() override;
    inline void setTarget(Character *character) { this->target = character; }
    virtual Vector2 computeDirection() override;
    virtual Vector2 getScreenPosition() override;
    virtual Rectangle getAttackArea() override;
    ~Enemy();

private:
    Texture2D hurt{LoadTexture("assets\\characters\\orc\\Orc-Hurt.png")};
    Character *target;
    float patrolledArea;
    Vector2 correctionFactor; //corrects the placement of the enemy against the target (from bottom corner to middle of the spritesheet)
    float range;
};

#endif
#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(const float map_scaling_factor, Vector2 position, Texture2D idle_texture, Texture2D running_texture, int numberOfFrames, Character * target);
    virtual void tick(float deltaTime) override;
    inline void setTarget(Character * character) {this->target = character; }
    virtual Vector2 computeDirection();
    ~Enemy();

private:
    Character * target;
};

#endif
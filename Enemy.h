#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCharacter.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(const float map_scaling_factor, Vector2 position, Texture2D idle_texture, Texture2D running_texture, int numberOfFrames);
    virtual void tick(float deltaTime) override;
    ~Enemy();

private:
};

#endif
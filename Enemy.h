#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCharacter.h"

#define STEP_SIZE_E 10.0f

class Enemy : public BaseCharacter
{
public:
    Enemy(const float map_scaling_factor, Vector2 position, Texture2D idle_texture, Texture2D running_texture, int numberOfFrames);
    void tick(float deltaTime);
    ~Enemy();

private:
};

#endif
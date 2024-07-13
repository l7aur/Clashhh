#ifndef CHARACTER_H
#define CHARACTER_H

#include "BaseCharacter.h"

#define CHARACTER_ROTATION_ANGLE 0.0f
#define STEP_SIZE 4.0f
#define MAP_SPAWNPOINT \
    {                  \
        2500, 1000     \
    }

class Character : public BaseCharacter
{
public:
    Character(const float map_scaling_factor, const int windowWidth, const int windowHeight);
    virtual void tick(float deltaTime) override;
    inline Vector2 getScreenPosition() { return this->screenPosition; }
    ~Character();

private:
};

#endif
#ifndef CHARACTER_H
#define CHARACTER_H

#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(const float map_scaling_factor, const int windowWidth, const int windowHeight, const float stepSize, Texture2D idle_texture, Texture2D running_texture);
    virtual void tick(float deltaTime) override;
    inline virtual Vector2 getScreenPosition() override;
    ~Character();

private:
    int windowWidth{};
    int windowHeight{};
};

#endif
#ifndef PROP_H
#define PROP_H

#include "raylib.h"

const float prop_rotation_angle = 0.0f;

class Prop
{
public:
    Prop(const float map_scaling_factor, const Vector2 worldPos, const Texture2D texture, const float scalingFactor);
    void render(Vector2 characterPosition);
    Rectangle getCollisionRec(Vector2 characterPosition);
    ~Prop();
    
private:
    Vector2 worldPosition{};
    Texture2D texture{};
    float scalingFactor{1.0};
};

#endif
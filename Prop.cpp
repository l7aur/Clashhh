#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 worldPos, Texture2D texture, float scalingFactor):
    worldPosition(worldPos),
    texture(texture),
    scalingFactor(scalingFactor)
{ }

void Prop::render(Vector2 characterPosition) {
    Vector2 screenPosition = Vector2Subtract(this->worldPosition, characterPosition);
    DrawTextureEx(this->texture, screenPosition, PROP_ROTATION_ANGLE, this->scalingFactor, WHITE);
}
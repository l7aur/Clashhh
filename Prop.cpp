#include "Prop.h"
#include "raymath.h"

Prop::Prop(const float map_scaling_factor, const Vector2 worldPos, const Texture2D texture, const float scalingFactor):
    worldPosition(Vector2Scale(worldPos, map_scaling_factor)),
    texture(texture),
    scalingFactor(scalingFactor)
{ }

void Prop::render(Vector2 characterPosition) {
    Vector2 screenPosition = Vector2Subtract(this->worldPosition, characterPosition);
    DrawTextureEx(this->texture, screenPosition, prop_rotation_angle, this->scalingFactor, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 characterPosition) {
    Vector2 screenPosition = Vector2Subtract(this->worldPosition, characterPosition);
    int minimize = 8;
    return Rectangle {
        screenPosition.x + minimize, screenPosition.y + minimize,
        this->texture.width * this->scalingFactor - 2 * minimize, this->texture.height * this->scalingFactor - 2 * minimize
    };
}

// Prop::~Prop() {
//     UnloadTexture(this->texture);
// }
#include "raylib.h"

#define PROP_ROTATION_ANGLE 0.0f

class Prop {
    public:
        Prop(Vector2 worldPos, Texture2D texture, float scalingFactor);
        void render(Vector2 characterPosition);
    private:
        Vector2 worldPosition{};
        Texture2D texture{};
        float scalingFactor{1.0};
};
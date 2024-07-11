#include "raylib.h"

#define PROP_SCALING_FACTOR 1.0f
#define PROP_ROTATION_ANGLE 0.0f

class Prop {
    public:
        Prop(Vector2 worldPos, Texture2D texture);
        void render(Vector2 characterPosition);
    private:
        Texture2D texture{};
        Vector2 worldPosition{};
};
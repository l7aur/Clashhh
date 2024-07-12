#include "raylib.h"

#define CHARACTER_ROTATION_ANGLE 0.0f
#define STEP_SIZE 4.0f
#define MAP_SPAWNPOINT {2500, 1000}

class Character
{
public:
    Character(const float map_scaling_factor, const int windowWidth, const int windowHeight);
    Vector2 getWorldPos() { return worldPosition; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();
    ~Character();

private:
    Vector2 computeDirection();

    Texture2D idle{LoadTexture("assets\\characters\\main_character\\_Idle.png")};
    Texture2D running{LoadTexture("assets\\characters\\main_character\\_Run.png")};
    Texture2D texture = idle;
    Vector2 screenPosition = {};
    Vector2 worldPosition = MAP_SPAWNPOINT;
    Vector2 pastWorldPosition{};
    int facingDirection{1};
    float runningTime{0.0f};
    int frame{0};
    const float updateTime{1.0f / 16.0f};
    const float speed = 5.0f;
    int width{};
    int height{};
    const int numberOfFrames{10};
    const float scale{2.0f};
};
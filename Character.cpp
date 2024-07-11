#include "Character.h"
#include "raymath.h"

Character::Character(const float map_scaling_factor) {
    this->width = this->texture.width / numberOfFrames;
    this->height = 40;
    this->worldPosition = Vector2Scale(this->worldPosition, map_scaling_factor);
}

void Character::setScreenPos(const int winWidth, const int winHeight)
{
    this->screenPosition = {(float)winWidth / 2.0f - this->width / 2.0f - 65.0f,
                            (float)winHeight / 2.0f - this->height / 2.0f - 25.0f};
}

void Character::tick(float deltaTime)
{
    Vector2 direction = {0.0f, 0.0f};
    if (IsKeyDown(KEY_A))
        direction.x -= STEP_SIZE;
    if (IsKeyDown(KEY_D))
        direction.x += STEP_SIZE;
    if (IsKeyDown(KEY_W))
        direction.y -= STEP_SIZE;
    if (IsKeyDown(KEY_S))
        direction.y += STEP_SIZE;

    if (Vector2Length(direction) > STEP_SIZE)
        direction = Vector2Scale(Vector2Normalize(direction), STEP_SIZE);
    this->pastWorldPosition = this->worldPosition;
    this->worldPosition = Vector2Add(this->worldPosition, direction);
    if (direction.x)
        (direction.x > 0) ? this->facingDirection = 1 : this->facingDirection = -1;
    (Vector2Length(direction)) ? this->texture = this->running : this->texture = this->idle;

    // change the frame of main character
    this->runningTime += deltaTime;
    if (this->runningTime >= this->updateTime)
    {
        this->runningTime = 0.0f;
        this->frame = (this->frame + 1) % 10;
    }
    // draw the main character
    DrawTexturePro(texture,
                   Rectangle{(float)(frame * width), 40.0f, (float)(facingDirection * width), (float)height},
                   Rectangle{screenPosition.x, screenPosition.y, CHARACTER_SCALING_FACTOR * (float)width, CHARACTER_SCALING_FACTOR * (float)height},
                   Vector2{},
                   CHARACTER_ROTATION_ANGLE,
                   WHITE);
}

void Character::undoMovement() {
    this->worldPosition = this->pastWorldPosition;
}
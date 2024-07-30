#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

const Vector2 spawnpoint = {2500, 1000};
enum STATE
{
    IDLE,
    ATTACKING,
    DEAD,
    RUNNING,
    HURT
};

class BaseCharacter
{
public:
    inline Vector2 getWorldPos() { return worldPosition; }
    inline void undoMovement() { this->worldPosition = this->pastWorldPosition; };
    virtual Rectangle getCollisionRec();
    virtual void tick(const float deltaTime);
    virtual Vector2 computeDirection();
    virtual Vector2 getScreenPosition() = 0; // pure virtual function => abstract class
    virtual Rectangle getAttackArea() = 0;
    void setHealthBar();
    inline float getHealth() const { return this->health; };
    inline float getMaximumHealth() const { return this->maximumHealth; };
    inline float getDamage() const { return this->damage; };
    inline void setDamage(float newDamage) { this->damage = newDamage; };
    inline void setHealth(int newHealth) { this->health = this->maximumHealth = newHealth; };
    inline int getFrame() const { return this->frame; };
    inline void takeDamage(float damageTaken) { this->health -= damageTaken; };
    inline STATE getState() const { return currentState; };
    inline void setState(STATE newState) { this->currentState = newState; };
    virtual ~BaseCharacter() {};

protected:
    Texture2D idle{};
    Texture2D death{LoadTexture("assets\\characters\\main_character\\_Death.png")};
    Texture2D running{};
    Texture2D attacking{};
    Texture2D hurt{};
    Texture2D texture{};
    Vector2 worldPosition{spawnpoint};
    Vector2 pastWorldPosition{};
    int facingDirection{1};
    float runningTime{0.0f};
    int frame{0};
    const float updateTime{1.0f / 16.0f};
    int width{};
    int height{};
    int numberOfFrames{1};
    int numberOfDeathFrames{1};
    const float scale{2.0f};
    float stepSize{0};

private:
    STATE currentState{IDLE};
    float health{100.0f};
    float maximumHealth{100.0f};
    float damage{0.0f};
};

#endif
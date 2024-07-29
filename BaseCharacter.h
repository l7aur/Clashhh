#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

const Vector2 spawnpoint = {2500, 1000};

class BaseCharacter
{
public:
    inline Vector2 getWorldPos() { return worldPosition; }
    void undoMovement();
    virtual Rectangle getCollisionRec();
    virtual void tick(float deltaTime); 
    virtual Vector2 computeDirection();
    virtual Vector2 getScreenPosition() = 0; //pure virtual function => abstract class
    virtual Rectangle getAttackArea() = 0;
    inline bool getAlive() const { return this->alive; };
    inline void setAlive(bool newState) { this->alive = newState; };
    inline int getHealth() const { return this->health; };
    inline float getDamage() const { return this->damage; };
    inline void setDamage(float newDamage) { this->damage = newDamage; };
    inline void setHealth(int newHealth) { this->health = newHealth; };
    inline int getFrame() const { return this->frame; };
    inline void takeDamage(float damageTaken) { this->health -= damageTaken; };
    ~BaseCharacter(); 
protected:

    Texture2D idle{};
    Texture2D death{LoadTexture("assets\\characters\\main_character\\_Death.png")};
    Texture2D running{};
    Texture2D attacking{};
    Texture2D texture{};
    Vector2 worldPosition{spawnpoint};
    Vector2 pastWorldPosition{};
    int facingDirection{1};
    float runningTime{0.0f};
    int frame{0};
    const float updateTime{1.0f / 16.0f};
    int width{};
    int height{};
    int numberOfFrames{10};
    const float scale{2.0f};
    float stepSize{0};
    bool attackingAnimation{false};
private:
    bool alive{true};
    unsigned int health{100};
    float damage{0};
};

#endif
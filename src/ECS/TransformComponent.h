#pragma once
#include "Components.h"
#include "./../Vector2D.h"

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;
    int speed = 3;

    TransformComponent(float xpos = 0.0f, float ypos = 0.0f)
    {
        position.x = xpos;
        position.y = ypos;
    }

    void init() override
    {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }
    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
    /*
    float xpos() { return position.x; }
    float ypos() { return position.y; }
    void setX(float newX) { position.x = newX; }
    void setY(float newY) { position.y = newY; }
    void setPos(float newX, float newY){ x = newX; y = newY; }
    */
};

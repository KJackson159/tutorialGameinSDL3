#pragma once
#include "Components.h"
#include "./../Vector2D.h"

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;

    TransformComponent(float xpos = 0.0f, float ypos = 0.0f){
        position.x = xpos;
        position.y = ypos;
    }

    void init() override{
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }
    void update() override{
        int speed = 3;
        if (velocity.x != 0 && velocity.y != 0) speed /= 1.414f; // Diagonal movement should be slower
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};

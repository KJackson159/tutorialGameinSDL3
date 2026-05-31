#pragma once
#include "../Vector2D.h"
#include "Components.h"
#include <cmath>

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
        float speed = PLAYERSPEED;
        // Diagonal movement should be slower to maintain consistent speed in all directions
        if (velocity.x != 0.0f && velocity.y != 0.0f) speed /= std::sqrt(2.0f);
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};

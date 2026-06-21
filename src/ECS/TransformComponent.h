#pragma once
#include "../Vector2D.h"
#include "Components.h"
#include <cmath>

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;
    short int width, height, scale;
    float speed;

    TransformComponent(
        float xpos = 0.0f, 
        float ypos = 0.0f, 
        short int w = FRAME_W, 
        short int h = FRAME_H, 
        short int sc = SCALE,
        float spd = PLAYERSPEED
    ){
        position.x = xpos;
        position.y = ypos;
        width = w;
        height = h;
        scale = sc;
        speed = spd;
    }

    void init() override{
        velocity.Zero();
    }
    
    void update() override{
        float estimatedSpeed = speed;
        // Diagonal movement should be slower to maintain consistent speed in all directions
        if (velocity.x != 0.0f && velocity.y != 0.0f) estimatedSpeed /= std::sqrt(2.0f);
        position.x += velocity.x * estimatedSpeed;
        position.y += velocity.y * estimatedSpeed;
    }
};

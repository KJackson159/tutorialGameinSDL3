#pragma once
#include <string>
#include <SDL3/SDL.h>
#include "Components.h"

class ColliderComponent : public Component
{
public:
    SDL_FRect collider;
    std::string tag;

    TransformComponent *transform;

    void init() override{
        if (!entity->hasComponent<TransformComponent>()) entity->addComponent<TransformComponent>();
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override{
        collider.x = transform->position.x;
        collider.y = transform->position.y;
        collider.w = FRAME_W * SCALE;
        collider.h = FRAME_H * SCALE;
    }
};

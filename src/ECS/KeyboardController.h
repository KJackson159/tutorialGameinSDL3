#pragma once
#include "Components.h"

class KeyboardController : public Component
{
public:
    TransformComponent *transform;

    void init() override{ transform = &entity->getComponent<TransformComponent>(); }

    void update() override{
        const bool *pressedKey = SDL_GetKeyboardState(nullptr);
        if (pressedKey[SDL_SCANCODE_W] || pressedKey[SDL_SCANCODE_UP])  transform->velocity.y = -1.0f;
        if (pressedKey[SDL_SCANCODE_S] || pressedKey[SDL_SCANCODE_DOWN]) transform->velocity.y = 1.0f;
        if (pressedKey[SDL_SCANCODE_A] || pressedKey[SDL_SCANCODE_LEFT]) transform->velocity.x = -1.0f;
        if (pressedKey[SDL_SCANCODE_D] || pressedKey[SDL_SCANCODE_RIGHT]) transform->velocity.x = 1.0f;
        
        if (!(pressedKey[SDL_SCANCODE_W] || pressedKey[SDL_SCANCODE_UP] || 
            pressedKey[SDL_SCANCODE_S] || pressedKey[SDL_SCANCODE_DOWN]) ||
            ((pressedKey[SDL_SCANCODE_W] || pressedKey[SDL_SCANCODE_UP]) && 
            (pressedKey[SDL_SCANCODE_S] || pressedKey[SDL_SCANCODE_DOWN])))  transform->velocity.y = 0.0f;

        if (!(pressedKey[SDL_SCANCODE_A] || pressedKey[SDL_SCANCODE_LEFT] || 
            pressedKey[SDL_SCANCODE_D] || pressedKey[SDL_SCANCODE_RIGHT]) ||
            ((pressedKey[SDL_SCANCODE_A] || pressedKey[SDL_SCANCODE_LEFT]) && 
            (pressedKey[SDL_SCANCODE_D] || pressedKey[SDL_SCANCODE_RIGHT])))  transform->velocity.x = 0.0f;
    }
};

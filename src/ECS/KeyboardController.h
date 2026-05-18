#pragma once

#include "./../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
    TransformComponent *transform;
    short int animation = 0; // 0-3 for idle animations, 4-7 for run animations

    void init() override{
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override{
        const bool *keyboard_state = SDL_GetKeyboardState(nullptr);
        if (keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_UP]) transform->velocity.y = -1;
        if (keyboard_state[SDL_SCANCODE_S] || keyboard_state[SDL_SCANCODE_DOWN]) transform->velocity.y = 1;
        if (keyboard_state[SDL_SCANCODE_A] || keyboard_state[SDL_SCANCODE_LEFT]) transform->velocity.x = -1;
        if (keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_RIGHT]) transform->velocity.x = 1;
        
        if (!(keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_UP] || 
            keyboard_state[SDL_SCANCODE_S] || keyboard_state[SDL_SCANCODE_DOWN])) transform->velocity.y = 0;
        if (!(keyboard_state[SDL_SCANCODE_A] || keyboard_state[SDL_SCANCODE_LEFT] || 
            keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_RIGHT])) transform->velocity.x = 0;
    }
};

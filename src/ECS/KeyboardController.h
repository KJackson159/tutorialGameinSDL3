#pragma once

#include "./../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
    TransformComponent *transform;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override
    {
        if (Game::event.type == SDL_EVENT_KEY_DOWN)
        {
            SDL_Keycode pressKey = Game::event.key.key;
            transform->velocity.x = (pressKey == SDLK_A || pressKey == SDLK_LEFT) ? -1
                                                                                  : ((pressKey == SDLK_D || pressKey == SDLK_RIGHT) ? 1 : transform->velocity.x);
            transform->velocity.y = (pressKey == SDLK_W || pressKey == SDLK_UP) ? -1 : ((pressKey == SDLK_S || pressKey == SDLK_DOWN) ? 1 : transform->velocity.y);
        }
        if (Game::event.type == SDL_EVENT_KEY_UP)
        {
            SDL_Keycode releaseKey = Game::event.key.key;
            transform->velocity.x = (releaseKey == SDLK_A || releaseKey == SDLK_LEFT || releaseKey == SDLK_D || releaseKey == SDLK_RIGHT) ? 0
                                                                                                                                          : transform->velocity.x;
            transform->velocity.y = (releaseKey == SDLK_W || releaseKey == SDLK_UP || releaseKey == SDLK_S || releaseKey == SDLK_DOWN) ? 0
                                                                                                                                       : transform->velocity.y;
        }
    }
};

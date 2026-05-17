#pragma once
#include "Components.h"
#include "./../TextureManager.h"
#include <SDL3/SDL.h>

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_FRect srcRect, destRect;

public:
    SpriteComponent() = default;
    SpriteComponent(const char *path) { setTexture(path); }

    void setTexture(const char *path)
    {
        if (texture)
            SDL_DestroyTexture(texture);
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0.0f;
        srcRect.w = srcRect.h = 16.0f;
        destRect.w = destRect.h = 32.0f;
    }
    void update() override
    {
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
    }
    void draw() override { TextureManager::Draw(texture, srcRect, destRect); }
};

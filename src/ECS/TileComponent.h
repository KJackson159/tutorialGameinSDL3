#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <SDL3/SDL.h>

class TileComponent : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_FRect tileRect;
    int tileID;
    std::string path;
    TileComponent() = default;

    TileComponent(float x, float y, float w, float h, int id){
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        switch (tileID){
            case 0: path = "./assets/Tile_Sprites/grass.png"; break;
            case 1: path = "./assets/Tile_Sprites/water.png"; break;
            case 2: path = "./assets/Tile_Sprites/dirt.png"; break;
            default: path = "./assets/Tile_Sprites/grass.png"; break;
        }
    }

    void init() override{
        entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
        transform = &entity->getComponent<TransformComponent>();
        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
};

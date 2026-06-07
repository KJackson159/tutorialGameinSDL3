#pragma once
#include "../TextureManager.h"
#include "Components.h"

class SpriteComponent : public Component
{
protected:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_FRect srcRect, destRect;

public:
    SpriteComponent() = default;
    SpriteComponent(const char* path){ setTexture(path); }

    ~SpriteComponent(){ SDL_DestroyTexture(texture); }

    void setTexture(const char* path){
        if (texture) SDL_DestroyTexture(texture);
        texture = TextureManager::LoadTexture(path);
    }

    void init() override{
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }  

    void update() override {
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
    }

    void draw() override { TextureManager::Draw(texture, srcRect, destRect); }
};


class SpritePlayerComponent : public SpriteComponent
{
private:
    std::vector<const char*> spriteSheets;
    short int animation = 0, frameNum = 0, cnt = 0; // 0-3 for idle animations, 4-7 for run animations
    short int prevAnimation = 0;

public:
    SpritePlayerComponent() = default;
    SpritePlayerComponent(std::vector<const char*> sheets){
        spriteSheets = sheets; 
        setTexture(spriteSheets[0]);
    }

    ~SpritePlayerComponent(){ SDL_DestroyTexture(texture); }

    void update() override{
        const bool *pressedKey = SDL_GetKeyboardState(nullptr);
        if (pressedKey[SDL_SCANCODE_W] || pressedKey[SDL_SCANCODE_UP]) animation = 7;
        if (pressedKey[SDL_SCANCODE_S] || pressedKey[SDL_SCANCODE_DOWN]) animation = 4;
        if (pressedKey[SDL_SCANCODE_A] || pressedKey[SDL_SCANCODE_LEFT]) animation = 5;
        if (pressedKey[SDL_SCANCODE_D] || pressedKey[SDL_SCANCODE_RIGHT]) animation = 6;
        /*
        if ((pressedKey[SDL_SCANCODE_W] || pressedKey[SDL_SCANCODE_UP]) && 
            (pressedKey[SDL_SCANCODE_D] || pressedKey[SDL_SCANCODE_RIGHT])) animation = 12; // Diagonal up right
        if ((pressedKey[SDL_SCANCODE_W] || pressedKey[SDL_SCANCODE_UP]) && 
            (pressedKey[SDL_SCANCODE_A] || pressedKey[SDL_SCANCODE_LEFT])) animation = 13; // Diagonal up left
        if ((pressedKey[SDL_SCANCODE_S] || pressedKey[SDL_SCANCODE_DOWN]) && 
            (pressedKey[SDL_SCANCODE_D] || pressedKey[SDL_SCANCODE_RIGHT])) animation = 14; // Diagonal down right
        if ((pressedKey[SDL_SCANCODE_S] || pressedKey[SDL_SCANCODE_DOWN]) && 
            (pressedKey[SDL_SCANCODE_A] || pressedKey[SDL_SCANCODE_LEFT])) animation = 15; // Diagonal down left
        */
        if ((destRect.x == (int)transform->position.x) && (destRect.y == (int)transform->position.y)){
             switch(animation){
                case 4: animation = 0; break; //down to idle down
                case 5: animation = 1; break; //left to idle left
                case 6: animation = 2; break; //right to idle right
                case 7: animation = 3; break; //up to idle up
                /*
                case 12: animation = 8; break; //diagonal up right to idle diagonal up right
                case 13: animation = 9; break; //diagonal up left to idle
                case 14: animation = 10; break; //diagonal down right to idle diagonal down right
                case 15: animation = 11; break; //diagonal down left to idle
                */
                default: break;
            }
        } setTexture(spriteSheets[animation]);
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        cnt++;
        if (cnt >= static_cast<int>(transform->speed)){                                         // Change frame every 1/10th second
            frameNum = (frameNum + 1) % N_FRAMES; // Assuming each animation has 6 frames
            cnt = 0;
        } srcRect.x = frameNum * FRAME_W;
    }
};

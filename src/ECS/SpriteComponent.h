#pragma once
#include "Components.h"
#include "./../TextureManager.h"
#include <SDL3/SDL.h>
#include <vector>

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_FRect srcRect, destRect;
    std::vector<const char*> paths = {
    "./assets/Char_Sprites/char_idle_down_anim_strip_6.png", //Idle down 0 (Initial animation)
    "./assets/Char_Sprites/char_idle_left_anim_strip_6.png", //Idle left 1
    "./assets/Char_Sprites/char_idle_right_anim_strip_6.png",//Idle right 2
    "./assets/Char_Sprites/char_idle_up_anim_strip_6.png",   //Idle up 3
    "./assets/Char_Sprites/char_run_down_anim_strip_6.png",  //Run down 4
    "./assets/Char_Sprites/char_run_left_anim_strip_6.png",  //Run left 5
    "./assets/Char_Sprites/char_run_right_anim_strip_6.png", //Run right 6
    "./assets/Char_Sprites/char_run_up_anim_strip_6.png"     //Run up 7
    };
    short int animation, frameNum, cnt; // 0-3 for idle animations, 4-7 for run animations
    short int prevAnimation;

public:
    SpriteComponent() { setTexture(0); } // Default to idle down animation
    ~SpriteComponent() { if (texture) SDL_DestroyTexture(texture); }

    void setTexture(const int pathIndex){
        if (texture) SDL_DestroyTexture(texture);
        texture = TextureManager::LoadTexture(paths.at(pathIndex));
    }

    void init() override{
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0.0f;
        srcRect.w = srcRect.h = 16.0f;
        destRect.w = destRect.h = 32.0f;
        animation = frameNum = cnt = 0;
    }

    void update() override{
        const bool *keyboard_state = SDL_GetKeyboardState(nullptr);
        if (keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_UP]) animation = 7;
        if (keyboard_state[SDL_SCANCODE_S] || keyboard_state[SDL_SCANCODE_DOWN]) animation = 4;
        if (keyboard_state[SDL_SCANCODE_A] || keyboard_state[SDL_SCANCODE_LEFT]) animation = 5;
        if (keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_RIGHT]) animation = 6;
        if ((destRect.x == (int)transform->position.x) && (destRect.y == (int)transform->position.y)){
             switch(animation){
                case 4: animation = 0; break; //down to idle down
                case 5: animation = 1; break; //left to idle left
                case 6: animation = 2; break; //right to idle right
                case 7: animation = 3; break; //up to idle up
            }
        } setTexture(animation);
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
        cnt++;
        if (cnt >= FPS / PLAYERSPEED){                                         // Change frame every 1/10th second
            frameNum = (frameNum + 1) % N_FRAMES; // Assuming each animation has 6 frames
            cnt = 0;
        } srcRect.x = frameNum * FRAME_W;
    }

    void draw() override { TextureManager::Draw(texture, srcRect, destRect); }
};

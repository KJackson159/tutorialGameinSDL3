#pragma once
#include "../TextureManager.h"
#include "Components.h"

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
    "./assets/Char_Sprites/char_run_up_anim_strip_6.png",     //Run up 7
    "idle diagonal up right", "idle diagonal up left", "idle diagonal down right", "idle diagonal down left", // Future diagonal animations 8-11
    "run diagonal up right", "run diagonal up left", "run diagonal down right", "run diagonal down left" // Future diagonal animations 12-15
    };
    short int animation, frameNum, cnt; // 0-3 for idle animations, 4-7 for run animations
    short int prevAnimation;

public:
    SpriteComponent() = default;
    SpriteComponent(const int pathIndex){ setTexture(pathIndex); }

    ~SpriteComponent(){ SDL_DestroyTexture(texture); }

    void setTexture(const int pathIndex){
        if (texture) SDL_DestroyTexture(texture);
        texture = TextureManager::LoadTexture(paths.at(pathIndex));
    }

    void init() override{
        transform = &entity->getComponent<TransformComponent>();
        srcRect.x = srcRect.y = 0.0f;
        srcRect.w = FRAME_W;
        srcRect.h = FRAME_H;
        destRect.w = FRAME_W * SCALE;
        destRect.h = FRAME_H * SCALE;
        animation = 2;
        frameNum = cnt = 0;
    }

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
        } setTexture(animation);
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
        cnt++;
        if (cnt >= (int)PLAYERSPEED){                                         // Change frame every 1/10th second
            frameNum = (frameNum + 1) % N_FRAMES; // Assuming each animation has 6 frames
            cnt = 0;
        } srcRect.x = frameNum * FRAME_W;
    }

    void draw() override { TextureManager::Draw(texture, srcRect, destRect); }
};

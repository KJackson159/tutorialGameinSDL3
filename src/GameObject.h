#pragma once
#include "Game.h"

class GameObject
{
public:
    GameObject(const char *texturesheet, int xpos = 0, int ypos = 0);
    ~GameObject();

    void Update(float deltaTime);
    void Render();

private:
    // int xpos, ypos;
    int cnt, frameNum;
    SDL_Texture *objTexture;
    SDL_FRect srcRect, destRect;
    // SDL_Renderer* renderer;
};

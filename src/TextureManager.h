#pragma once

#include "Game.h"

class TextureManager
{
public:
    static SDL_Texture *LoadTexture(std::string file);
    static void Draw(SDL_Texture *tex, SDL_FRect src, SDL_FRect dest);
};

#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char *file)
{
    SDL_Texture *texture = IMG_LoadTexture(Game::renderer, file);
    if (!texture)
    {
        SDL_Log("Failed to load texture %s: %s", file, SDL_GetError());
    }
    else
    {
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    }
    return texture;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_FRect src, SDL_FRect dest)
{
    SDL_RenderTexture(Game::renderer, tex, &src, &dest);
}

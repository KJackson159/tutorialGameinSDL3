#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(std::string file){
    SDL_Texture *texture = IMG_LoadTexture(Game::renderer, file.c_str());
    if (!texture) SDL_Log("Failed to load texture %s: %s", file.c_str(), SDL_GetError());
    else SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    return texture;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_FRect src, SDL_FRect dest){
    // Apply camera offset to destination rectangle
    if (Game::camera){
        Vector2D offset = Game::camera->getOffset();
        dest.x += offset.x;
        dest.y += offset.y;
    }
    SDL_RenderTexture(Game::renderer, tex, &src, &dest);
}

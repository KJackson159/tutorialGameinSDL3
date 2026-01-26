#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *texturesheet, int xpos, int ypos)
{ // Default parameters for xpos and ypos
    cnt = 0, frameNum = 0;
    // renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet);
    // xpos = 0, ypos = 0;
    srcRect.x = 0, srcRect.y = 0;
    srcRect.w = FRAME_W, srcRect.h = FRAME_H;
    destRect.x = xpos, destRect.y = ypos;
    destRect.w = srcRect.w, destRect.h = srcRect.h;
}
GameObject::~GameObject()
{
    // SDL_DestroyTexture(objTexture);
}

void GameObject::Update(float deltaTime)
{
    cnt++;
    destRect.x += PLAYERSPEED * deltaTime;
    destRect.y += PLAYERSPEED * deltaTime;

    if (cnt == FPS / 10)
    {                                         // Change frame every 1/10th second
        frameNum = (frameNum + 1) % N_FRAMES; // Assuming each animation has 6 frames
        cnt = 0;
    }
    srcRect.x = frameNum * FRAME_W;
}

void GameObject::Render()
{
    SDL_RenderTexture(Game::renderer, objTexture, &srcRect, &destRect);
}

#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Camera.h"

class Game
{
public:
    Game();
    ~Game();

    void init(const char *title);

    void handleEvents();
    void update();
    void render();
    void timeDelay(float frameTime);
    void clean();
    bool running() { return isRunning; }

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static Camera *camera;

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Surface *iconSurface;
};

#endif /* Game_hpp */

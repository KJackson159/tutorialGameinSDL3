#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#define WINDOW_W 1280
#define WINDOW_H 720

#define N_FRAMES 6
#define FRAME_W 16
#define FRAME_H 16

#define PLAYERSPEED 3.0f
#define FPS 40
#define FRAME_TARGET_TIME (1000/FPS) // aka frame delay in milliseconds

class Camera;

class Game
{
public:
    Game();
    ~Game();

    void init(const char *title, int width, int height);

    void handleEvents();
    void update();
    void render();
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

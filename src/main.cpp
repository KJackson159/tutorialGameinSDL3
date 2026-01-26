#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{

    float frameStart, frameEnd, frameTime;

    game = new Game();
    game->init("Prototype Game 2", WINDOW_W, WINDOW_H);

    while (game->running())
    {
        frameEnd = SDL_GetTicks();

        game->handleEvents();
        game->update(frameStart); // delta time in seconds (frameCurr-frameLast) / 1000.0f
        game->render();

        frameTime = SDL_GetTicks() - frameEnd;
        if (FRAME_TARGET_TIME > frameTime)
        {
            SDL_Delay(FRAME_TARGET_TIME - frameTime); // cap the frame rate for consistency
        }
        frameStart = frameEnd;
    }

    game->clean();
    delete game;
    return 0;
}

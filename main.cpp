#include "src/Game.h"

Game *game = nullptr;

int main(int argc, char *argv[]){

    float frameStart, frameEnd;

    game = new Game();
    game->init("Prototype Game 2");

    while (game->running()){
        frameEnd = SDL_GetTicks();

        game->handleEvents();
        game->update(); // delta time in seconds (frameCurr-frameLast) / 1000.0f
        game->render();

        game->timeDelay(SDL_GetTicks() - frameEnd);
        frameStart = frameEnd;
    }

    game->clean();
    delete game;
    return 0;
}

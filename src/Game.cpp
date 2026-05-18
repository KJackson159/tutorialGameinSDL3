#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"

Map *gameMap;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
auto &player(manager.addEntity());

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int width, int height){
    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Error initializing SDL: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE); // SDL_CreateWindow("Lesson 1: My first window from SDL", WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE);
    if (!window){
        SDL_Log("Error creating window: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer){
        SDL_Log("Error creating renderer: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    isRunning = true;
    SDL_SetRenderLogicalPresentation(renderer, WINDOW_W/4, WINDOW_H/4, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    gameMap = new Map();
    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>();
    player.addComponent<KeyboardController>();
}

void Game::handleEvents(){
    // SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_EVENT_QUIT: isRunning = false; break;
        default: break;
    }
}

void Game::update(){
    manager.refresh();
    manager.update();
}

void Game::render(){
    SDL_RenderClear(renderer);
    gameMap->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("Game Cleaned up successfully!\n");
}

#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Collision.h"
#include "ECS/Components.h"
#include "ECS/Sprites.h"

Map *gameMap;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
Camera *Game::camera = nullptr;

auto &player(manager.addEntity());
auto &wall(manager.addEntity());

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title){
    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Error initializing SDL: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    window = SDL_CreateWindow(title, WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE); // SDL_CreateWindow("Lesson 1: My first window from SDL", WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE);
    if (!window){
        SDL_Log("Error creating window: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    iconSurface = IMG_Load("./assets/test.png");
    if (!iconSurface){
        SDL_Log("Failed to load icon image: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }
    SDL_SetWindowIcon(window, iconSurface);
    SDL_DestroySurface(iconSurface);

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer){
        SDL_Log("Error creating renderer: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    isRunning = true;
    SDL_SetRenderLogicalPresentation(renderer, WINDOW_W/4, WINDOW_H/4, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    gameMap = new Map();
    camera = new Camera();
    player.addComponent<TransformComponent>();
    player.addComponent<SpritePlayerComponent>(playerSprites);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");

    wall.addComponent<TransformComponent>(50.0f, 50.0f, 100, 20);
    wall.addComponent<SpriteComponent>("assets/Tile_Sprites/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents(){
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_EVENT_QUIT: isRunning = false; break;
        default: break;
    }
}

void Game::update(){
    manager.refresh();
    // Update camera to follow player
    camera->update(&player.getComponent<TransformComponent>());
    manager.update();
    if (Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider)){
        SDL_Log("Collision Detected!");
        player.getComponent<TransformComponent>().position = Vector2D(0.0f, 0.0f); // Reset player position on collision
    }
}

void Game::render(){
    SDL_RenderClear(renderer);
    gameMap->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

// cap the frame rate for consistency
void Game::timeDelay(float frameTime){
    if (FRAME_TARGET_TIME > frameTime) SDL_Delay(FRAME_TARGET_TIME - frameTime);
}

void Game::clean(){
    delete gameMap;
    delete camera;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("Game Cleaned up successfully!\n");
}

#include "Game.h"
#include "TextureManager.h"
// #include "GameObject.h"
#include "Map.h"
// #include "ECS/ECS.h"
#include "ECS/Components.h"

// SDL_Texture* player_texture = nullptr;
// SDL_FRect srcRect = {0,0,FRAME_W,FRAME_H}, destRect;
// GameObject *player;
// GameObject *enemy;

Map *gameMap;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
auto &player(manager.addEntity());

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int width, int height)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Error initializing SDL: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE); // SDL_CreateWindow("Lesson 1: My first window from SDL", WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        SDL_Log("Error creating window: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        SDL_Log("Error creating renderer: %s\n", SDL_GetError());
        isRunning = false;
        return;
    }

    isRunning = true;
    SDL_SetRenderLogicalPresentation(renderer, WINDOW_W / 4, WINDOW_H / 4, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    gameMap = new Map();
    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("./assets/Char_Sprites/char_run_right_anim_strip_6.png");
    player.addComponent<KeyboardController>();
}

void Game::handleEvents()
{
    // SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_EVENT_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::update(float frameStart)
{
    manager.refresh();
    manager.update();
    if (player.getComponent<TransformComponent>().position.x > 60.0f)
    {
        player.getComponent<SpriteComponent>().setTexture("./assets/Enemies_Sprites/Pinkslime_Sprites/pinkslime_run_anim_anim_all_dir_strip_6.png");
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    gameMap->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("Game Cleaned up successfully!\n");
}

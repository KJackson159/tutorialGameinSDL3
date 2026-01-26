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
    // SDL_Surface* temp_surface = IMG_Load("assets/Char_Sprites/char_idle_down_anim_strip_6.png");
    // player_texture = TextureManager::LoadTexture("./assets/Char_Sprites/char_run_right_anim_strip_6.png", renderer);//SDL_CreateTextureFromSurface(renderer, temp_surface);
    // SDL_DestroySurface(temp_surface);
    // player = new GameObject("./assets/Char_Sprites/char_run_right_anim_strip_6.png", 20);
    // enemy = new GameObject("./assets/Enemies_Sprites/Pinkslime_Sprites/pinkslime_run_anim_anim_all_dir_strip_6.png", 200, 150);
    gameMap = new Map();
    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("./assets/Char_Sprites/char_run_right_anim_strip_6.png");
    player.addComponent<KeyboardController>();
    // newPlayer.addComponent<PositionComponent>();
    // newPlayer.getComponent<PositionComponent>().setPos(100.0f, 100.0f);
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
    // float deltaTime = (SDL_GetTicks() - frameStart) / 1000.0f;
    // player->Update(deltaTime);
    // enemy->Update(-deltaTime / 2.0f);
    manager.refresh();
    manager.update();
    // player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));
    if (player.getComponent<TransformComponent>().position.x > 60.0f)
    {
        player.getComponent<SpriteComponent>().setTexture("./assets/Enemies_Sprites/Pinkslime_Sprites/pinkslime_run_anim_anim_all_dir_strip_6.png");
    }
    // std::cout << newPlayer.getComponent<PositionComponent>().xpos() << ", " << newPlayer.getComponent<PositionComponent>().ypos() << std::endl;
}

void Game::render()
{
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    gameMap->DrawMap();
    manager.draw();
    // Render game objects here
    // player->Render();
    // enemy->Render();
    // SDL_RenderTexture(renderer, player_texture, &srcRect, &destRect);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_Log("Game Cleaned up successfully!\n");
}

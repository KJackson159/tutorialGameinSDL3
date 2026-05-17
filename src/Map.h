#pragma once
#include "Game.h"

#define MAP_COLS 25
#define MAP_ROWS 20

class Map
{
public:
    Map();
    ~Map();

    void LoadMap(int arr[MAP_ROWS][MAP_COLS]);
    void DrawMap();

private:
    SDL_Texture *dirt, *grass, *water;
    SDL_FRect src, dest;
    int map[MAP_ROWS][MAP_COLS];
};

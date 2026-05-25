#include "Map.h"
#include "TextureManager.h"

int lvl1[MAP_ROWS][MAP_COLS] = {0};

Map::Map()
{
    dirt = TextureManager::LoadTexture("./assets/Tile_Sprites/dirt.png");
    grass = TextureManager::LoadTexture("./assets/Tile_Sprites/grass.png");
    water = TextureManager::LoadTexture("./assets/Tile_Sprites/water.png");

    LoadMap(lvl1);
    src.x = src.y = 0;
    src.w = dest.w = 16;
    src.h = dest.h = 16;
    dest.x = dest.y = 0;
}

Map::~Map() {}

void Map::LoadMap(int arr[MAP_ROWS][MAP_COLS]){
    for (int i = 0; i < MAP_ROWS; i++){
        for (int j = 0; j < MAP_COLS; j++) map[i][j] = arr[i][j];
    }
}

void Map::DrawMap(){
    for (int i = 0; i < MAP_ROWS; i++){
        for (int j = 0; j < MAP_COLS; j++){
            dest.x = j * 16;
            dest.y = i * 16;

            switch (map[i][j]){
                case 0: TextureManager::Draw(water, src, dest); break;
                case 1: TextureManager::Draw(grass, src, dest); break;
                case 2: TextureManager::Draw(dirt, src, dest); break;
                default: break;
            }
        }
    }
}

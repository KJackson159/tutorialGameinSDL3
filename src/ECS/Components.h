#pragma once

#define WINDOW_W 1280
#define WINDOW_H 720

#define N_FRAMES 6
#define FRAME_W 16
#define FRAME_H 16
#define SCALE 2

#define PLAYERSPEED 3.0f
#define FPS 40

#define FRAME_TARGET_TIME (1000/FPS) // aka frame delay in milliseconds

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "KeyboardController.h"
#include "ColliderComponent.h"
#include "TileComponent.h"

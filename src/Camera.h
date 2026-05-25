#pragma once
#include "Vector2D.h"

class TransformComponent;

class Camera
{
private:
    Vector2D position;
    float width;
    float height;
    
    // Deadzone threshold - how far the player can move before camera follows
    // This is the distance from camera center where player starts forcing camera movement
    float deadzoneX;
    float deadzoneY;

    // Map dimensions in pixels
    float mapWidth;
    float mapHeight;

public:
    Camera();
    ~Camera();

    // Getters for camera position and dimensions
    float getX() const { return position.x; }
    float getY() const { return position.y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

    // Update camera position based on player position
    void update(TransformComponent *player);

    // Get offset for rendering (negative of camera position)
    Vector2D getOffset() const{ return Vector2D(-position.x, -position.y); }
};

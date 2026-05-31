#include "Camera.h"
#include "ECS/Components.h"

Camera::Camera()
    : width(WINDOW_W / 4.0f), height(WINDOW_H / 4.0f),
      deadzoneX(width * 0.25f), deadzoneY(height * 0.25f),
      mapWidth(25 * 16), mapHeight(20 * 16)
{
    position.x = 0.0f;
    position.y = 0.0f;
}

Camera::~Camera() {}

void Camera::update(TransformComponent *player){
    if (!player) return;

    // Get player center position
    float playerCenterX = player->position.x + (FRAME_W / 2.0f);
    float playerCenterY = player->position.y + (FRAME_H / 2.0f);

    // Get camera center position
    float cameraCenterX = position.x + (width / 2.0f);
    float cameraCenterY = position.y + (height / 2.0f);

    // Calculate distance from player to camera center
    float distX = playerCenterX - cameraCenterX;
    float distY = playerCenterY - cameraCenterY;

    // Move camera if player exceeds deadzone
    if (distX > deadzoneX) position.x += (distX - deadzoneX);
    else if (distX < -deadzoneX) position.x += (distX + deadzoneX);

    if (distY > deadzoneY) position.y += (distY - deadzoneY);
    else if (distY < -deadzoneY) position.y += (distY + deadzoneY);

    // Clamp camera to map boundaries
    // Left boundary
    if (position.x < 0.0f) position.x = 0.0f;
    // Right boundary
    if (position.x + width > mapWidth) position.x = mapWidth - width;
    // Top boundary
    if (position.y < 0.0f) position.y = 0.0f;
    // Bottom boundary
    if (position.y + height > mapHeight) position.y = mapHeight - height;
}

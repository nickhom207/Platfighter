#include "CollisionManager.hpp"
#include <iostream>




CollisionManager::CollisionManager() {

}
CollisionManager::~CollisionManager() {

}

bool CollisionManager::CheckCollision(const Rectangle& rect1, const Rectangle& rect2, float deltaTime) {
    // Calculate the future position of the rectangles
    float rect1FutureX = rect1.x + rect1.velocityX * deltaTime;
    float rect1FutureY = rect1.y + rect1.velocityY * deltaTime;
    float rect2FutureX = rect2.x + rect2.velocityX * deltaTime;
    float rect2FutureY = rect2.y + rect2.velocityY * deltaTime;

    // Calculate the future intersection parameters
    float futureLeft = std::max(rect1FutureX, rect2FutureX);
    float futureRight = std::min(rect1FutureX + rect1.width, rect2FutureX + rect2.width);
    float futureTop = std::max(rect1FutureY, rect2FutureY);
    float futureBottom = std::min(rect1FutureY + rect1.height, rect2FutureY + rect2.height);

    // Check if there is a future intersection
    if (futureLeft < futureRight && futureTop < futureBottom) {
        // Calculate the time of collision on each axis
        float collisionTimeX = (futureLeft - futureRight) / (rect1.velocityX - rect2.velocityX);
        float collisionTimeY = (futureTop - futureBottom) / (rect1.velocityY - rect2.velocityY);

        // Check if the collision occurs within the given time interval
        if (collisionTimeX >= 0 && collisionTimeX <= deltaTime &&
            collisionTimeY >= 0 && collisionTimeY <= deltaTime) {
            return true; // Collision detected
        }
    }

    return false; // No collision
}

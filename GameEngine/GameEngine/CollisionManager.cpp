#include "CollisionManager.hpp"
#include <iostream>
#include <vector>




CollisionManager::CollisionManager() {

}
CollisionManager::~CollisionManager() {

}

bool CollisionManager::CheckCollision(const SDL_Rect a, const SDL_Rect b, SDL_Point a_speed, float deltaTime) {

    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //Update sides base on it's future movement
    if (a_speed.x > 0) {
        rightA = rightA + a_speed.x;
    }
    else {
        leftA = leftA - a_speed.x;
    }

    if (a_speed.y > 0) {
        topA = topA + a_speed.y;
    }
    else {
        bottomA = bottomA - a_speed.y;
    }

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
    /*
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
    */
}


// Structure to represent a polygon
struct Polygon
{
    std::vector<SDL_Point> points;
};

// Function to check if two line segments intersect
bool doLineSegmentsIntersect(SDL_Point p1, SDL_Point q1, SDL_Point p2, SDL_Point q2)
{
    int o1 = (q1.x - p1.x) * (p2.y - p1.y) - (p2.x - p1.x) * (q1.y - p1.y);
    int o2 = (q1.x - p1.x) * (q2.y - p1.y) - (q2.x - p1.x) * (q1.y - p1.y);
    int o3 = (q2.x - p2.x) * (p1.y - p2.y) - (p1.x - p2.x) * (q2.y - p2.y);
    int o4 = (q2.x - p2.x) * (q1.y - p2.y) - (q1.x - p2.x) * (q2.y - p2.y);

    if ((o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0) || (o3 > 0 && o4 < 0) || (o3 < 0 && o4 > 0))
        return true;

    if (o1 == 0 && (p2.x - p1.x) * (p2.x - q1.x) <= 0 && (p2.y - p1.y) * (p2.y - q1.y) <= 0)
        return true;

    if (o2 == 0 && (p2.x - p1.x) * (p2.x - q1.x) <= 0 && (p2.y - p1.y) * (p2.y - q1.y) <= 0)
        return true;

    if (o3 == 0 && (q2.x - p2.x) * (q2.x - q1.x) <= 0 && (q2.y - p2.y) * (q2.y - q1.y) <= 0)
        return true;

    if (o4 == 0 && (q2.x - p2.x) * (q2.x - q1.x) <= 0 && (q2.y - p2.y) * (q2.y - q1.y) <= 0)
        return true;

    return false;
}

// Function to check if two polygons intersect
bool doPolygonsIntersect(const Polygon& polygon1, const Polygon& polygon2)
{
    int n1 = polygon1.points.size();
    int n2 = polygon2.points.size();

    for (int i = 0; i < n1; i++)
    {
        int j = (i + 1) % n1;
        for (int k = 0; k < n2; k++)
        {
            int l = (k + 1) % n2;
            if (doLineSegmentsIntersect(polygon1.points[i], polygon1.points[j], polygon2.points[k], polygon2.points[l]))
                return true;
        }
    }

    return false;
}
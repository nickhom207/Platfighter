#pragma once
#include "Game.hpp"

struct Rectangle {
	float x, y; // Top-left corner position
	float width, height;
	float velocityX, velocityY; // Velocity of the rectangle
};

class CollisionManager {
public:
	CollisionManager();
	~CollisionManager();
	bool CheckCollision(SDL_Point p1, SDL_Point q1, SDL_Point p2, SDL_Point q2, SDL_Point a_speed, float deltaTime);
private:

};


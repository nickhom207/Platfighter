#ifndef Collision_hpp
#define Collision_hpp
#include "SDL.h"

struct Rectangle {
	float x, y; // Top-left corner position
	float width, height;
	float velocityX, velocityY; // Velocity of the rectangle
};

class CollisionManager {
public:
	CollisionManager();
	~CollisionManager();
	bool CheckCollision(const SDL_Rect a, const SDL_Rect b, SDL_Point a_speed, float deltaTime);
private:

};

#endif /* CollisionManager_hpp */

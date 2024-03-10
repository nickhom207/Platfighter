#pragma once
#include "Game.hpp"

class GameObject {

public:
	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

	SDL_Point GetCollisionTopLeftPoint();
	SDL_Point GetCollisionBottomRightPoint();
	SDL_Point GetSpeed();

private:
	int xpos;
	int ypos;

	int height;
	int width;
	SDL_Point topLeftPoint;
	SDL_Point bottomRightPoint;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};
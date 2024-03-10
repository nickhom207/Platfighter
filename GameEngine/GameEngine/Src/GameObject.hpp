#pragma once
#include "Game.hpp"

class GameObject {

public:
	GameObject(const char* texturesheet, int x, int y, int h, int w);
	~GameObject();

	void Update();
	void Render();
	void MoveHorizontal(int command);
	void Jump();
	void SetSpeed(int x, int y);
	SDL_Point GetCollisionTopLeftPoint();
	SDL_Point GetCollisionBottomRightPoint();
	SDL_Point GetSpeed();

private:
	int xpos;
	int ypos;
	int ystart;
	int xspeed;
	int yspeed;

	int height;
	int width;
	SDL_Point topLeftPoint;
	SDL_Point bottomRightPoint;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};
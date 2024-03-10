#pragma once
#include "Game.hpp"

class PlayerObject {

public:
	PlayerObject(const char* texturesheet, int x, int y);
	~PlayerObject();

	void Update();
	void Render();
	void MoveHorizontal(int command);
	void Jump();

	SDL_Point GetCollisionTopLeftPoint();
	SDL_Point GetCollisionBottomRightPoint();
	SDL_Point GetSpeed();

private:
	int xpos;
	int ypos;
	int ystart;

	int xspeed;
	int yspeed;
	int xmaxspeed;
	int ymaxspeed;
	int xacceleration;
	int yacceleration;
	int xdecceleration;
	int ydecceleration;
	int jumpforce;
	int fallspeed;

	int width;
	int height;
	SDL_Point topLeftPoint;
	SDL_Point bottomRightPoint;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};
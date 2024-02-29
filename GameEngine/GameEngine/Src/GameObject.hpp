#pragma once
#include "Game.hpp"

class GameObject {

public:
	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	void Update();
	void Render();
	void MoveHorizontal(int command);
	void Jump();

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

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};
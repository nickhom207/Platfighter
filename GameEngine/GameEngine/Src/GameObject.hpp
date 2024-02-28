#pragma once
#include "Game.hpp"

class GameObject {

public:
	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	void Update();
	void Render();
	void Move(int command);

private:
	int xpos;
	int ypos;

	int xspeed;
	int yspeed;
	int xmaxspeed;
	int ymaxspeed;
	int xacceleration;
	int yacceleration;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};
#pragma once
#include "Game.hpp"

class DummyObject {

public:
	DummyObject(const char* texturesheet, int x, int y);
	~DummyObject();

	void Update();
	void Render();
	void SetSpeed(int x, int y);

	void setY(int y);
	void respawn();
	void setYspeed(int y);
	void setXspeed(int x);
	void knockBack(int x, int y);
	void receiveDamage(double dmg);

	SDL_Point GetCollisionTopLeftPoint();
	SDL_Point GetCollisionBottomRightPoint();

private:
	int xpos;
	int ypos;
	int xspeed;
	int yspeed;
	int fallspeed;

	int height;
	int width;
	SDL_Point topLeftPoint;
	SDL_Point bottomRightPoint;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

	double damage;
};


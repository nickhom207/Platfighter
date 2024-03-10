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

	void setY(int y);
	void respawn();
	void setYspeed(int y);
	void giveJump();

	int GetXPos();
	int GetYPos();

	SDL_Point GetCollisionTopLeftPoint();
	SDL_Point GetCollisionBottomRightPoint();
	SDL_Point GetSpeed();

	bool shootingCooldown;
	void CoolDown();

private:
	int xpos;
	int ypos;

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
	bool hasJump;

	int width;
	int height;
	SDL_Point topLeftPoint;
	SDL_Point bottomRightPoint;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};
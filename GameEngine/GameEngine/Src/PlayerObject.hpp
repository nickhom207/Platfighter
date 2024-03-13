#pragma once
#include "Game.hpp"

class PlayerObject {

public:
	PlayerObject(const char* texturesheet, int x, int y, int maxspeed, int acceleration, int deceleration, int jump, int fall);
	~PlayerObject();

	void Update();
	void Render();

	void MoveHorizontal(int command);
	void Jump();
	void DoubleJump();

	void setY(int y);
	void setIgnorePlat(bool x);
	void setFallingPlat(bool x);
	void setThroughPlat(bool x);
	void setYspeed(int y);
	
	void respawn();
	void ground();

	int GetXPos();
	int GetYPos();
	int GetH();
	int GetW();
	bool GetGround();

	SDL_Point GetCollisionTopLeftPoint();
	SDL_Point GetCollisionBottomRightPoint();
	SDL_Point GetSpeed();

	bool shootingCooldown;
	bool isFacingRight;
	bool isGrounded;
	bool hasJump;
	bool hasDblJump;
	bool isFallingOffPlatform;
	bool isThroughPlatform;
	bool ignorePlatform;

private:
	int xpos;
	int ypos;

	int xspeed;
	int yspeed;
	int xmaxspeed;
	int xacceleration;
	int xdeceleration;
	int jumpforce;
	int fallspeed;

	int width;
	int height;
	SDL_Point topLeftPoint;
	SDL_Point bottomRightPoint;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};
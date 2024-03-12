#pragma once
#include "Game.hpp"
#include "PlayerObject.hpp"

class Hitbox {

public:
	Hitbox(PlayerObject* character, int x, int y, int h, int w, double d, int kb, double a);
	~Hitbox();

	void Update();
	void Activate();
	void Deactivate();

	int getXknockback();
	int getReverseXknockback();
	int getYknockback();
	double getDamage();
	bool isActive();

	SDL_Point GetCollisionTopLeftPoint();
	SDL_Point GetCollisionBottomRightPoint();

private:
	PlayerObject* player;
	double angle;
	int xoffset, yoffset, xpos, ypos, height, width, knockback;
	double damage;
	bool active;

	SDL_Point topLeftPoint;
	SDL_Point bottomRightPoint;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};
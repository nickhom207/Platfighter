#pragma once
#include "Game.hpp"
#include "PlayerObject.hpp"

class Hitbox {

public:
	Hitbox(PlayerObject* character, int x, int y, int h, int w, double dmg, int kb, double a, int frames);
	~Hitbox();

	void Update();
	void Trigger();
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
	double angle, damage;
	int xoffset, yoffset, xpos, ypos, height, width, knockback, frames, counter;
	bool active;

	SDL_Point topLeftPoint;
	SDL_Point bottomRightPoint;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};
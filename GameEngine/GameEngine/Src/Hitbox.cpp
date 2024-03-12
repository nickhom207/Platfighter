#include "Hitbox.hpp"
#include <cmath>

Hitbox::Hitbox(PlayerObject* character, int x, int y, int h, int w, int power, int kb, double a) {
	player = character;
	xoffset = x;
	yoffset = y;
	xpos = player->GetXPos() + xoffset;
	ypos = player->GetYPos() + yoffset;
	height = h;
	width = w;
	damage = power;
	knockback = kb;
	angle = a;
	active = false;

	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height };
}

void Hitbox::Update() {
	xpos = player->GetXPos() + xoffset;
	ypos = player->GetYPos() + yoffset;

	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height };
}

void Hitbox::Activate() {
	xpos = player->GetXPos() + xoffset;
	ypos = player->GetYPos() + yoffset;

	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height };
}

void Hitbox::Deactivate() {
	active = false;
}

int Hitbox::getXknockback() {
	return cos(angle) * knockback;
}

int Hitbox::getYknockback() {
	return sin(angle) * knockback;
}

SDL_Point Hitbox::GetCollisionTopLeftPoint() {
	return topLeftPoint;
}

SDL_Point Hitbox::GetCollisionBottomRightPoint() {
	return bottomRightPoint;
}
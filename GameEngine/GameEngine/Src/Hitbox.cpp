#include "Hitbox.hpp"
#include <cmath>

Hitbox::Hitbox(PlayerObject* character, int x, int y, int h, int w, double d, int kb, double a, int duration) {
	player = character;
	xoffset = x;
	yoffset = y;
	xpos = player->GetXPos() + xoffset;
	ypos = player->GetYPos() + yoffset;
	height = h;
	width = w;
	damage = d;
	knockback = kb;
	angle = a;
	frames = duration;
	active = false;
	//arbitrarily high number
	counter = 100;

	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height };
}

void Hitbox::Update() {
	if (counter < frames)
		counter++;
	else
		active = false;
}

void Hitbox::Trigger() {
 	active = true;

	xpos = player->GetXPos() + xoffset;
	ypos = player->GetYPos() + yoffset;

	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height };

	counter = 0;
}

void Hitbox::Deactivate() {
	active = false;
}

void Hitbox::Activate() {
	active = true;
}

int Hitbox::getXknockback() {
	return cos(angle) * knockback;
}

int Hitbox::getReverseXknockback() {
	return cos(angle) * knockback * -1;
}

int Hitbox::getYknockback() {
	return sin(angle) * knockback;
}

double Hitbox::getDamage() {
	return damage;
}

bool Hitbox::isActive() {
	return active;
}

SDL_Point Hitbox::GetCollisionTopLeftPoint() {
	return topLeftPoint;
}

SDL_Point Hitbox::GetCollisionBottomRightPoint() {
	return bottomRightPoint;
}
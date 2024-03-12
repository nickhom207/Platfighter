#include "DummyObject.hpp"
#include "TextureManager.hpp"

DummyObject::DummyObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;

	xspeed = 0;
	yspeed = 0;
	fallspeed = -5;

	width = 64;
	height = 64;
	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height };

	damage = 1;
}

void DummyObject::Update()
{
	/*std::cout << xspeed << std::endl;*/
	/*std::cout << yspeed << std::endl;*/

	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	xpos += xspeed;
	yspeed -= fallspeed;
	ypos += yspeed;

	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height };
}

void DummyObject::Render()
{
	if(damage <= 20)
		SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
	else
		SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &destRect, NULL, NULL, SDL_FLIP_VERTICAL);
		
}

SDL_Point DummyObject::GetCollisionTopLeftPoint() {
	return topLeftPoint;
}

SDL_Point DummyObject::GetCollisionBottomRightPoint() {
	return bottomRightPoint;
}

void DummyObject::SetSpeed(int x, int y) {
	xspeed = x;
	yspeed = y;

}

void DummyObject::setY(int y) {
	ypos = y;
}

void DummyObject::respawn() {
	xpos = 608;
	ypos = 0;
	yspeed = 1;
	xspeed = 0;
	damage = 0;
}

void DummyObject::setYspeed(int y) {
	yspeed = y;
}

void DummyObject::setXspeed(int x) {
	xspeed = x;
}

void DummyObject::knockBack(int x, int y) {
	xspeed += x * damage;
	yspeed += y * damage;
}

void DummyObject::receiveDamage(double dmg) {
	damage += dmg;
}
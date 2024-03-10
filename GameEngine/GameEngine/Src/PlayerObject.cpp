#include "PlayerObject.hpp"
#include "TextureManager.hpp"

PlayerObject::PlayerObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;

	xspeed = 0;
	yspeed = 0;
	xmaxspeed = 20;
	ymaxspeed = 20;
	xacceleration = 2;
	yacceleration = 2;
	xdecceleration = 2;
	ydecceleration = 2;
	jumpforce = 50;
	fallspeed = -5;
	hasJump = false;
	
	width = 64;
	height = 64;
	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height };
}

void PlayerObject::Update()
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

void PlayerObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

void PlayerObject::MoveHorizontal(int command) {
	switch (command) {
		/*left*/
	case 0:
		if (xspeed > xmaxspeed * -1)
			xspeed -= xacceleration;
		break;
		/*right*/
	case 1:
		if (xspeed < xmaxspeed)
			xspeed += xacceleration;
		break;
		/*stopping*/
	case 2:
		xspeed /= xdecceleration;
		break;
	default:
		break;
	}
}

void PlayerObject::Jump() {
	if (yspeed == 0 && hasJump) {
		yspeed = -jumpforce;
		hasJump = false;
	}
}


void PlayerObject::setY(int y) {
	ypos = y;
}

void PlayerObject::respawn() {
	xpos = 608;
	ypos = 0;
	yspeed = 1;
	xspeed = 0;
}

void PlayerObject::setYspeed(int y) {
	yspeed = y;
}

void PlayerObject::giveJump() {
	hasJump = true;
}

SDL_Point PlayerObject::GetCollisionTopLeftPoint() {
	return topLeftPoint;
}

SDL_Point PlayerObject::GetCollisionBottomRightPoint() {
	return bottomRightPoint;
}

SDL_Point PlayerObject::GetSpeed() {
	return SDL_Point{ xspeed, yspeed };
}

int PlayerObject::GetXPos() {
	return xpos;
}
int PlayerObject::GetYPos() {
	return ypos;
}

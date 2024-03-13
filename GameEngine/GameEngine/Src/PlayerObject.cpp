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
	hasJump = true;
	hasDblJump = false;
	isGrounded = true;
	isFallingOffPlatform = true;
	isThroughPlatform = false;
	ignorePlatform = true;
	
	width = 64;
	height = 64;
	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height };
	isFacingRight = true;
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
	if(isFacingRight)
		SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
	else
		SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &destRect, NULL, NULL, SDL_FLIP_HORIZONTAL);
}

void PlayerObject::MoveHorizontal(int command) {
	switch (command) {
		/*left*/
	case 0:
		isFacingRight = false;
		if (xspeed > xmaxspeed * -1)
			xspeed -= xacceleration;
		break;
		/*right*/
	case 1:
		isFacingRight = true;
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
		isGrounded = false;
	}
}

void PlayerObject::DoubleJump() {
	if (!hasJump and hasDblJump) {
		yspeed = 0 - jumpforce;
		hasDblJump = false;
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

void PlayerObject::ground() {
	isGrounded = true;
	hasJump = true;
	hasDblJump = true;
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

int PlayerObject::GetH() {
	return height;
}
int PlayerObject::GetW() {
	return width;
}
bool PlayerObject::GetGround() {
	return isGrounded;
}

void PlayerObject::setFallingPlat(bool x) {
	isFallingOffPlatform = x;
}

void PlayerObject::setIgnorePlat(bool x) {
	ignorePlatform = x;
}

void PlayerObject::setThroughPlat(bool x) {
	isThroughPlatform = x;
}


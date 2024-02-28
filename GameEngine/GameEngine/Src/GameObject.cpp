#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y)
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
}

void GameObject::Update()
{
	std::cout << xspeed << std::endl;
	std::cout << yspeed << std::endl;

	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

void GameObject::Move(int command) {
	switch (command) {
	case 0:
		if(yspeed < ymaxspeed)
			yspeed += yacceleration;
		ypos -= yspeed;
		break;
	case 1:
		if (xspeed < xmaxspeed)
			xspeed += xacceleration;
		xpos -= xspeed;
		break;
	case 2:
		if (yspeed < ymaxspeed)
			yspeed += yacceleration;
		ypos += yspeed;
		break;
	case 3:
		if (xspeed < xmaxspeed)
			xspeed += xacceleration;
		xpos += xspeed;
		break;
	default:
		if (xspeed > 0)
			xspeed -= xacceleration;
		if (yspeed > 0)
			yspeed -= yacceleration;
		break;
	}
}
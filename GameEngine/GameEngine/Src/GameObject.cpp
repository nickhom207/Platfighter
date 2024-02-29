#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
	ystart = y;
	
	xspeed = 0;
	yspeed = 0;
	xmaxspeed = 20;
	ymaxspeed = 20;
	xacceleration = 2;
	yacceleration = 2;
}

void GameObject::Update()
{
	/*std::cout << xspeed << std::endl;*/
	std::cout << yspeed << std::endl;

	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	xpos += xspeed;
	if (ypos < ystart)
		yspeed += 5;
	else if (ypos > ystart)
		yspeed = 0;
	if (ypos + yspeed > ystart)
	{
		ypos = ystart;
		yspeed = 0;
	}
	else
		ypos += yspeed;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

void GameObject::Move(int command) {
	switch (command) {
	/*jump*/
	case 0:
		if(yspeed == 0)
			yspeed = -50;
		break;
	/*left*/
	case 1:
		if (xspeed < xmaxspeed and xspeed > xmaxspeed * -1)
			xspeed -= xacceleration;
		break;
	case 2:
		break;
	/*right*/
	case 3:
		if (xspeed < xmaxspeed and xspeed > xmaxspeed * -1)
			xspeed += xacceleration;
		break;
	/*stopping*/
	case 4:
		xspeed /= 2;
		break;
	default:
		break;
	}
}

void GameObject::Move2() {
	
}
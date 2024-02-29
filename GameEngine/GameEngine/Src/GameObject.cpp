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
	xdecceleration = 2;
	ydecceleration = 2;
	jumpforce = 50;
	fallspeed = -5;
}

void GameObject::Update()
{
	std::cout << xspeed << std::endl;
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
	if (ypos < ystart)
		yspeed -= fallspeed;
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

void GameObject::MoveHorizontal(int command) {
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

void GameObject::Jump() {
	if (ypos == ystart and yspeed == 0)
		yspeed = -jumpforce;
}
#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
	
	xmaxspeed = 10;
	ymaxspeed = 10;
	xacceleration = 2;
	yacceleration = 2;
}

void GameObject::Update()
{
	srcRect.h = 64;
	srcRect.w = 64;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

void GameObject::Move(int command) {
	switch (command) {
	case 0:
		ypos += yspeed;
		break;
	case 1:
		xpos -= xspeed;
		break;
	case 2:
		ypos -= yspeed;
		break;
	case 3:
		xpos += xspeed;
		break;
	default:
		break;
	}
}
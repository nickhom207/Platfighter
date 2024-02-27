#include "GameObject.hpp"

GameObject::GameObject(SDL_Renderer* ren)
{
	renderer = ren;
	objectTexture = nullptr;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 0;
	srcRect.h = 0;

	destRect.x = 0;
	destRect.y = 0;
	destRect.w = 0;
	destRect.h = 0;

	xpos = 0;
	ypos = 0;
}

void GameObject::Update()
{
	xpos = 0;
	ypos = 0;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

}

void GameObject::Render()
{
	SDL_RenderCopy(renderer, objectTexture,&srcRect, &destRect);
}
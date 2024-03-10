#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;

	height = 64;
	width = 64;
	topLeftPoint = SDL_Point{ xpos - width / 2 , ypos + height / 2 };
	bottomRightPoint = SDL_Point{ xpos + width / 2 , ypos - height / 2 };
}

void GameObject::Update()
{
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

SDL_Point GameObject::GetCollisionTopLeftPoint() {
	return topLeftPoint;
}

SDL_Point GameObject::GetCollisionBottomRightPoint() {
	return bottomRightPoint;
}
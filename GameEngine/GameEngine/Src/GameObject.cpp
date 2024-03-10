#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y, int h, int w)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
	ystart = y;
	xspeed = 0;
	yspeed = 0;

	//Collision:
	height = h;
	width = w;
	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height};
}

void GameObject::Update()
{
	srcRect.h = height;
	srcRect.w = width;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;

	xpos += xspeed;
	ypos += yspeed;

	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height };

	/*
	//Collision
	topLeftPoint = SDL_Point{ xpos, ypos };
	bottomRightPoint = SDL_Point{ xpos + width, ypos + height };*/
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

void GameObject::SetSpeed(int x, int y) {
	xspeed = x;
	yspeed = y;

}
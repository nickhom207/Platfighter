#pragma once
#include "Game.hpp"

class Map
{
public:
	Map();
	~Map();
	void LoadMap(int arr[23][40]);
	void DrawMap();

private:
	SDL_Rect src, dest;
	SDL_Texture* block;
	SDL_Texture* space;

	int map[23][40];
};
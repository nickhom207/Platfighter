#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "CollisionManager.hpp"

GameObject* player;
Map* map;
SDL_Renderer* Game::renderer = nullptr;
CollisionManager collisionManager;
SDL_Rect rect1, rect2;


Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsustems Initialized" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	player = new GameObject("assets/face.png", 0, 0);
	map = new Map();
	rect1 = { 0, 0, 10, 10 };
	rect2 = { 15, 0, 5, 5 }; // TestingUse

}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_w:
				player->Move(0);
				break;
			case SDLK_a:
				player->Move(1);
				break;
			case SDLK_s:
				player->Move(2);
				break;
			case SDLK_d:
				player->Move(3);
				break;
			default:
				break;
			}
		default:
			break;
	}
}

void Game::update()
{
	player->Update();
	/*
	cnt++;
	std::cout << cnt << std::endl; */

	if (collisionManager.CheckCollision(rect1, rect2, { 50, 0 }, 1.0f / 60.0f)) {
		std::cout << "Collision detected!" << std::endl;
	}
	else {
		std::cout << "Collision NOT detected!" << std::endl;
	}

}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	player->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}
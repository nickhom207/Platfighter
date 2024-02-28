#include "Game.hpp"
#include "CollisionManager.hpp"

Game::Game()
{}
Game::~Game()
{}



CollisionManager collisionManager;
SDL_Rect rect1, rect2;

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

	//For testing:
	rect1 = { 0, 0, 10, 10 };
	rect2 = { 15, 0, 5, 5 }; // Modified starting position and velocity
	
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update()
{
	cnt++;
	std::cout << cnt << std::endl;

	//for testing

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
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}
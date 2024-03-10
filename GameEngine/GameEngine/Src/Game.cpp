#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "PlayerObject.hpp"
#include "Map.hpp"
#include "CollisionManager.hpp"

PlayerObject* player;
GameObject* box;
Map* map;
SDL_Renderer* Game::renderer = nullptr;
CollisionManager collisionManager;

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

	player = new PlayerObject("assets/face.png", 400, 512);
	box = new GameObject("red)square.png", 500, 512);
	map = new Map();
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

void Game::getInputs()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_A] and keystate[SDL_SCANCODE_D])
	{
		player->MoveHorizontal(2);
	}
	else if (keystate[SDL_SCANCODE_A])
	{
		player->MoveHorizontal(0);
	}
	else if (keystate[SDL_SCANCODE_D])
	{
		player->MoveHorizontal(1);
	}
	else
	{
		player->MoveHorizontal(2);
	}

	if (keystate[SDL_SCANCODE_W])
	{
		player->Jump();
	}
}

void Game::update()
{
	player->Update();
	if (collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), box->GetCollisionTopLeftPoint(), box->GetCollisionBottomRightPoint(), player->GetSpeed(), (1.0f / 60.0f))) {
		std::cout << "Collision detected!" << std::endl;
	}
	else {
		std::cout << "Collision NOT detected!" << std::endl;
	}

	/*
	cnt++;
	std::cout << cnt << std::endl; */
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
#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "PlayerObject.hpp"
#include "Map.hpp"
#include "Audio.hpp"
#include "CollisionManager.hpp"

PlayerObject* player;
GameObject* lowerBound;
GameObject* leftBound;
GameObject* rightBound;
GameObject* stage;
Audio sound;
Map* map;
SDL_Renderer* Game::renderer = nullptr;
CollisionManager collisionManager;

Game::Game()
{}
Game::~Game()
{}

bool jumpSound = false;

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		SDL_Init(SDL_INIT_EVERYTHING);

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
	lowerBound = new GameObject("assets/red_square.png", 0, 1000, 4, 2000);
	leftBound = new GameObject("assets/red_square.png", -100, 360, 900, 4);
	rightBound = new GameObject("assets/red_square.png", 1400, 360, 900, 4);
	stage = new GameObject("assets/main_platform.png", 192, 576, 64, 896);
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
		sound.load("assets/jump.wav");
		if (!jumpSound)
		{
			sound.load("assets/jump.wav");
			sound.play();
			jumpSound = true;
		}
	}
	else
	{
		jumpSound = false;
	}
}

void Game::update()
{
	player->Update();
	lowerBound->Update();
	stage->Update();
	//stage collision
	if (collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), stage->GetCollisionTopLeftPoint(), stage->GetCollisionBottomRightPoint(), player->GetSpeed(), (1.0f / 60.0f))) {
		player->setY(stage->GetCollisionTopLeftPoint().y - 64);
		player->setYspeed(0);
		player->giveJump();
	}
	//outer bounds collision
	if (collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), lowerBound->GetCollisionTopLeftPoint(), lowerBound->GetCollisionBottomRightPoint(), player->GetSpeed(), (1.0f / 60.0f))
		or collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), leftBound->GetCollisionTopLeftPoint(), leftBound->GetCollisionBottomRightPoint(), player->GetSpeed(), (1.0f / 60.0f))
		or collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), rightBound->GetCollisionTopLeftPoint(), rightBound->GetCollisionBottomRightPoint(), player->GetSpeed(), (1.0f / 60.0f))) {
		player->respawn();
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	lowerBound->Render();
	stage->Render();
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
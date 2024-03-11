#include <vector> 
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
std::vector<GameObject*> attacks;
std::vector<GameObject*> targets;
Map* map;
SDL_Renderer* Game::renderer = nullptr;
CollisionManager collisionManager;
Audio sound;

int jump;
int shoot;
int respawnSound;

bool keysPressed[SDL_NUM_SCANCODES] = { false };

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

	sound.INIT_Mixer();
	int jump = sound.loadSound("Assets/jump.wav");
	int shoot = sound.loadSound("Assets/shoot.wav");
	std::cout << shoot << std::endl;
	int respawnSound = sound.loadSound("Assets/respawn.wav");

	player = new PlayerObject("assets/face.png", 400, 512);
	lowerBound = new GameObject("assets/red_square.png", 0, 1000, 4, 2000);
	leftBound = new GameObject("assets/red_square.png", -100, 360, 900, 4);
	rightBound = new GameObject("assets/red_square.png", 1400, 360, 900, 4);
	stage = new GameObject("assets/main_platform.png", 192, 576, 64, 896);
	GameObject* target = new GameObject("assets/blue_square.png", 192, 500, 32, 32);
	targets.push_back(target);
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

bool isJumping = false;
bool isShooting = false;

void Game::getInputs()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			keysPressed[event.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			keysPressed[event.key.keysym.scancode] = false;
			break;
		default:
			break;
		}
	}

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

	//single activiation input
	if (keysPressed[SDL_SCANCODE_W] and !isJumping) {
		player->Jump();
		isJumping = true;
		int pan = ((player->GetXPos() - 640) * 100) / 640;
		sound.playSound(jump, pan);
	}
	if(!keysPressed[SDL_SCANCODE_W]) {
		isJumping = false;
	}
	if (keysPressed[SDL_SCANCODE_F] and !isShooting) {
		GameObject* attack = new GameObject("assets/blue_square.png", player->GetXPos(), player->GetYPos(), 18, 18);
		if (player->isFacingRight) {
			attack->SetSpeed(10, 0);
		}
		else {
			attack->SetSpeed(-10, 0);
		}
		int pan = ((player->GetXPos() - 640) * 100) / 640;
		sound.playSound(1, pan);
		attacks.push_back(attack);
		isShooting = true;
	}
	if (!keysPressed[SDL_SCANCODE_F]) {
		isShooting = false;
	}

}
void Game::update()
{
	player->Update();
	lowerBound->Update();
	stage->Update();
	if (attacks.size() != 0) {
		for (int i = 0; i < attacks.size(); i++) {
			attacks[i]->Update();
		}
	}
	
	if (targets.size() != 0) {
		for (int i = 0; i < targets.size(); i++) {
			targets[i]->Update();
		}
	}
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
		int pan = ((player->GetXPos() - 640) * 100) / 640;
		sound.playSound(2, pan);
	}
	
	if (attacks.size() != 0 && targets.size() != 0) {
		for (int i = 0; i < attacks.size(); i++) {
			for (int j = 0; j < targets.size(); j++) {
				if (collisionManager.CheckCollision(attacks[i]->GetCollisionTopLeftPoint(), attacks[i]->GetCollisionBottomRightPoint(), targets[j]->GetCollisionTopLeftPoint(), targets[j]->GetCollisionBottomRightPoint(), attacks[i]->GetSpeed(), (1.0f / 60.0f))) {
					std::cout << "Shooted target" << std::endl;
				}
			}
		}
	}


}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	lowerBound->Render();
	stage->Render();
	player->Render();
	if (attacks.size() != 0) {
		for (int i = 0; i < attacks.size(); i++) {
			attacks[i]->Render();
		}
	}
	
	if (targets.size() != 0) {
		for (int i = 0; i < targets.size(); i++) {
			targets[i]->Render();
		}
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	sound.QUIT_Mixer();
	std::cout << "Game cleaned" << std::endl;
}
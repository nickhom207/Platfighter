#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "PlayerObject.hpp"
#include "DummyObject.hpp"
#include "Hitbox.hpp"
#include "Map.hpp"
#include "Audio.hpp"
#include "CollisionManager.hpp"

PlayerObject* player;
GameObject *lowerBound, *leftBound, *rightBound, *stage, *platform1;
DummyObject* dummy;
Hitbox* left, * right;
std::vector<GameObject*> attacks;
std::vector<GameObject*> targets;
Map* map;
SDL_Renderer* Game::renderer = nullptr;
CollisionManager collisionManager;
Audio sound;

int jump;
int shoot;
int respawnSound;
int surfaceHit;

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
	int respawnSound = sound.loadSound("Assets/respawn.wav");
	int surfaceHit = sound.loadSound("Assets/surfacehit.wav");

	player = new PlayerObject("assets/face.png", 400, 512);
	left = new Hitbox(player, 0, 0, 64, 32, 2, 10, M_PI / 2.5 * -1);
	right = new Hitbox(player, 33, 0, 64, 32, 2, 10, M_PI / 2.5);
	dummy = new DummyObject("assets/dummy.png", 192, 500);
	lowerBound = new GameObject("assets/red_square.png", 0, 1000, 4, 2000);
	leftBound = new GameObject("assets/red_square.png", -100, 360, 950, 4);
	rightBound = new GameObject("assets/red_square.png", 1400, 360, 950, 4);
	stage = new GameObject("assets/main_platform.png", 192, 576, 64, 896);
	platform1 = new GameObject("assets/main_platform.png", 300, 400, 20, 200);
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

bool isShooting = false;
bool isJumping = false;
bool isGrounded = true;
bool isThroughPlatform = false;
bool isFallingOffPlatform = false;
bool ignorePlatform = true;

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
	if (keysPressed[SDL_SCANCODE_W] and isGrounded and !isJumping) {
		player->Jump();
		int pan = ((player->GetXPos() - 640) * 100) / 640;
		sound.playSound(jump, pan, 50);
		isJumping = true;
	}
	if (!keysPressed[SDL_SCANCODE_W] and isJumping) {
		isJumping = false;
	}

	if (keysPressed[SDL_SCANCODE_SPACE] and !isShooting) {
		int pan = ((player->GetXPos() - 640) * 100) / 640;
		sound.playSound(1, pan, 50);
		left->Activate();
		right->Activate();
		isShooting = true;
	}
	if (!keysPressed[SDL_SCANCODE_SPACE] and isShooting) {
		isShooting = false;
	}
	if (keysPressed[SDL_SCANCODE_S] and !isFallingOffPlatform) {
		isFallingOffPlatform = true;
		ignorePlatform = false;
	}
	if (!keysPressed[SDL_SCANCODE_S] and isFallingOffPlatform) {
		isFallingOffPlatform = false;
	}

	/*
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
	*/

}
void Game::update()
{
	player->Update();
	//left->Update();
	//right->Update();
	std::cout << player->GetSpeed().y << std::endl;
	dummy->Update();
	stage->Update();
	platform1->Update();
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

	bool checkPlatformCollision = collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), platform1->GetCollisionTopLeftPoint(), platform1->GetCollisionBottomRightPoint());
	bool checkStageCollision = collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), stage->GetCollisionTopLeftPoint(), stage->GetCollisionBottomRightPoint());

	//player-stage collision
	if (checkStageCollision) {
		player->setY(stage->GetCollisionTopLeftPoint().y - 64);
		int tempSpeed = abs(player->GetSpeed().y);
		player->setYspeed(0);
		player->giveJump();
		if (!isGrounded) {
			int pan = ((player->GetXPos() - 640) * 100) / 640;
			sound.playSound(3, pan, tempSpeed*1.5);
			isGrounded = true;
			ignorePlatform = true;
			//std::cout << isGrounded << std::endl;
		}
	}

	if (!checkStageCollision and !checkPlatformCollision) {
		isGrounded = false;
	}

	//player-platform collision
	if (checkPlatformCollision) {
		if (player->GetSpeed().y > 0) {
			if (checkPlatformCollision and (player->GetYPos() < platform1->GetCollisionTopLeftPoint().y) and ignorePlatform) {
				isThroughPlatform = true;
				player->setY(platform1->GetCollisionTopLeftPoint().y - 64);
				int tempSpeed = abs(player->GetSpeed().y);
				player->setYspeed(0);
				player->giveJump();

				if (!isGrounded) {
					int pan = ((player->GetXPos() - 640) * 100) / 640;
					sound.playSound(3, pan, tempSpeed*1.5);
					isGrounded = true;
				}
			}
		}
	}

	//dummy-stage collision
	if (collisionManager.CheckCollision(dummy->GetCollisionTopLeftPoint(), dummy->GetCollisionBottomRightPoint(), stage->GetCollisionTopLeftPoint(), stage->GetCollisionBottomRightPoint())) {
		dummy->setY(stage->GetCollisionTopLeftPoint().y - 64);
		dummy->setYspeed(0);
		dummy->setXspeed(0);
	}

	//player-outer bounds collision
	if (collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), lowerBound->GetCollisionTopLeftPoint(), lowerBound->GetCollisionBottomRightPoint())
		or collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), leftBound->GetCollisionTopLeftPoint(), leftBound->GetCollisionBottomRightPoint())
		or collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), rightBound->GetCollisionTopLeftPoint(), rightBound->GetCollisionBottomRightPoint())) {
		player->respawn();
		isGrounded = false;
		int pan = ((player->GetXPos() - 640) * 100) / 640;
		sound.playSound(2, pan, 50);
	}

	//dummy-outer bounds collision
	if (collisionManager.CheckCollision(dummy->GetCollisionTopLeftPoint(), dummy->GetCollisionBottomRightPoint(), lowerBound->GetCollisionTopLeftPoint(), lowerBound->GetCollisionBottomRightPoint())
		or collisionManager.CheckCollision(dummy->GetCollisionTopLeftPoint(), dummy->GetCollisionBottomRightPoint(), leftBound->GetCollisionTopLeftPoint(), leftBound->GetCollisionBottomRightPoint())
		or collisionManager.CheckCollision(dummy->GetCollisionTopLeftPoint(), dummy->GetCollisionBottomRightPoint(), rightBound->GetCollisionTopLeftPoint(), rightBound->GetCollisionBottomRightPoint())) {
		dummy->respawn();
	}

	//hitbox-dummy collision
	//if (collisionManager.CheckCollision(dummy->GetCollisionTopLeftPoint(), dummy->GetCollisionBottomRightPoint(), left->GetCollisionTopLeftPoint(), left->GetCollisionBottomRightPoint())) {
	//	dummy->knockBack(left->getXknockback(), -1 * left->getYknockback());
	//	std::cout << "hit l" << std::endl;
	//}
	if (collisionManager.CheckCollision(dummy->GetCollisionTopLeftPoint(), dummy->GetCollisionBottomRightPoint(), right->GetCollisionTopLeftPoint(), right->GetCollisionBottomRightPoint())) {
		dummy->knockBack(right->getXknockback(), -1 * right->getYknockback());
		std::cout << "hit r" << std::endl;
	}
	
	if (attacks.size() != 0 && targets.size() != 0) {
		for (int i = 0; i < attacks.size(); i++) {
			for (int j = 0; j < targets.size(); j++) {
				if (collisionManager.CheckCollision(attacks[i]->GetCollisionTopLeftPoint(), attacks[i]->GetCollisionBottomRightPoint(), targets[j]->GetCollisionTopLeftPoint(), targets[j]->GetCollisionBottomRightPoint())) {
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
	stage->Render();
	platform1->Render();
	player->Render();
	dummy->Render();
	if (attacks.size() != 0) {
		for (int i = 0; i < attacks.size(); i++) {
			attacks[i]->Render();
		}
	}
	
	/*
	if (targets.size() != 0) {
		for (int i = 0; i < targets.size(); i++) {
			targets[i]->Render();
		}
	}*/

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
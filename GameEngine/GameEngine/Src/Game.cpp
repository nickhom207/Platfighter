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
GameObject *lowerBound, *leftBound, *rightBound, *stage, *platform1, *platform2;
DummyObject* dummy;
Hitbox* melee;
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
	melee = new Hitbox(player, 0, 0, 64, 64, 0.5, 5, M_PI / 2.5);
	dummy = new DummyObject("assets/dummy.png", 500, 512);
	lowerBound = new GameObject("assets/red_square.png", -10, 1000, 4, 2000);
	leftBound = new GameObject("assets/red_square.png", -100, -360, 1900, 4);
	rightBound = new GameObject("assets/red_square.png", 1400, -360, 1900, 4);
	stage = new GameObject("assets/main_platform.png", 192, 576, 8, 896);
	platform1 = new GameObject("assets/main_platform.png", 300, 400, 8, 200);
	platform2 = new GameObject("assets/main_platform.png", 780, 400, 8, 200);
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
bool isSingleJumping = false;
bool isJumpKey = false;

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

	//single activation input for jump
	if (keysPressed[SDL_SCANCODE_W] and player->isGrounded and !isJumpKey) {
		player->Jump();
		int pan = ((player->GetXPos() - 640) * 100) / 640;
		sound.playSound(jump, pan, 50);
		isSingleJumping = true;
		isJumpKey = true;
	}
	if (!keysPressed[SDL_SCANCODE_W] and player->isGrounded and isJumpKey) {
		isJumpKey = false;
	}

	//single activation input for falling (platform)
	if (keysPressed[SDL_SCANCODE_S] and !player->isFallingOffPlatform) {
		player->setFallingPlat(true);
		player->setIgnorePlat(false);
	}
	if (!keysPressed[SDL_SCANCODE_S] and player->isFallingOffPlatform) {
		player->setFallingPlat(false);
	}

	//double jump
	if (keysPressed[SDL_SCANCODE_W] and !player->isGrounded and player->hasDblJump and !isSingleJumping) {
		player->DoubleJump();
		int pan = ((player->GetXPos() - 640) * 100) / 640;
		sound.playSound(jump, pan, 50);
	}
	if (!keysPressed[SDL_SCANCODE_W]) {
		isSingleJumping = false;
	}

	//melee attack
	if (keysPressed[SDL_SCANCODE_SPACE] and !isShooting) {
		int pan = ((player->GetXPos() - 640) * 100) / 640;
		sound.playSound(1, pan, 50);
		melee->Activate();
		isShooting = true;
	}
	if (!keysPressed[SDL_SCANCODE_SPACE]) {
		isShooting = false;
	}

	//respawn all
	if (keysPressed[SDL_SCANCODE_R]) {
		melee->Deactivate();
		player->respawn();
		dummy->respawn();
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
	dummy->Update();
	stage->Update();
	platform1->Update();
	platform2->Update();
	
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

	//collision check variables
	bool checkStageColl = collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), stage->GetCollisionTopLeftPoint(), stage->GetCollisionBottomRightPoint());
	bool checkPlatform1Coll = collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), platform1->GetCollisionTopLeftPoint(), platform1->GetCollisionBottomRightPoint());
	bool checkPlatform2Coll = collisionManager.CheckCollision(player->GetCollisionTopLeftPoint(), player->GetCollisionBottomRightPoint(), platform2->GetCollisionTopLeftPoint(), platform2->GetCollisionBottomRightPoint());

	if (!checkStageColl and !checkPlatform1Coll and !checkPlatform2Coll) {
		player->isGrounded = false;
		player->hasJump = false;
	}

	//player-stage collision
	if (checkStageColl) {
		player->setY(stage->GetCollisionTopLeftPoint().y - 64);
		int tempSpeed = abs(player->GetSpeed().y);
		player->setYspeed(0);
		player->setIgnorePlat(true);
		if (!player->GetGround()) {
			int pan = ((player->GetXPos() - 640) * 100) / 640;
			sound.playSound(3, pan, tempSpeed*1.7);
			player->ground();
		}
	}

	//player-platform collision
	//platform1
	if (checkPlatform1Coll) {
		if (player->GetSpeed().y > 0) {
			if(player->GetYPos() < platform1->GetCollisionTopLeftPoint().y and player->ignorePlatform) {
				player->setThroughPlat(true);
				player->setY(platform1->GetCollisionTopLeftPoint().y - 64);
				int tempSpeed = abs(player->GetSpeed().y);
				player->setYspeed(0);
				if (!player->GetGround()) {
					int pan = ((player->GetXPos() - 640) * 100) / 640;
					sound.playSound(3, pan, tempSpeed * 1.7);
					player->ground();
				}
			}
		}
	}

	//platform2
	if (checkPlatform2Coll) {
		if (player->GetSpeed().y > 0) {
			if (player->GetYPos() < platform2->GetCollisionTopLeftPoint().y and player->ignorePlatform) {
				player->setThroughPlat(true);
				player->setY(platform2->GetCollisionTopLeftPoint().y - 64);
				int tempSpeed = abs(player->GetSpeed().y);
				player->setYspeed(0);
				if (!player->GetGround()) {
					int pan = ((player->GetXPos() - 640) * 100) / 640;
					sound.playSound(3, pan, tempSpeed * 1.7);
					player->ground();
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
		int pan = ((player->GetXPos() - 640) * 100) / 640;
		//sorry the sound was annoying me lol
		//sound.playSound(2, pan);
	}

	//dummy-outer bounds collision
	if (collisionManager.CheckCollision(dummy->GetCollisionTopLeftPoint(), dummy->GetCollisionBottomRightPoint(), lowerBound->GetCollisionTopLeftPoint(), lowerBound->GetCollisionBottomRightPoint())
		or collisionManager.CheckCollision(dummy->GetCollisionTopLeftPoint(), dummy->GetCollisionBottomRightPoint(), leftBound->GetCollisionTopLeftPoint(), leftBound->GetCollisionBottomRightPoint())
		or collisionManager.CheckCollision(dummy->GetCollisionTopLeftPoint(), dummy->GetCollisionBottomRightPoint(), rightBound->GetCollisionTopLeftPoint(), rightBound->GetCollisionBottomRightPoint())) {
		dummy->respawn();
	}

	//hitbox-dummy collision
	if (melee->isActive() and collisionManager.CheckCollision(dummy->GetCollisionTopLeftPoint(), dummy->GetCollisionBottomRightPoint(), melee->GetCollisionTopLeftPoint(), melee->GetCollisionBottomRightPoint())) {
		if(player->isFacingRight)
			dummy->knockBack(melee->getXknockback(), -1 * melee->getYknockback());
		else
			dummy->knockBack(melee->getReverseXknockback(), -1 * melee->getYknockback());
		dummy->receiveDamage(melee->getDamage());

		std::cout << "Hit!" << std::endl;
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
	dummy->Render();
	player->Render();
	platform1->Render();
	platform2->Render();
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
#ifndef Game_hpp
#define Game_hpp
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#undef main

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();
	void getInputs();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;

private:
	int cnt;
	bool isRunning;
	SDL_Window *window;
};

#endif /* Game_hpp */
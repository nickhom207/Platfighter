#include "SDL.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	bool isRunning = true;
	SDL_Event event;

	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
		}
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	return 0;
}
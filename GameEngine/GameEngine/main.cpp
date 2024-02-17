#include "Game.hpp"

Game* game = nullptr;

int main(int argc, const char* argv[]) {
	game = new Game();

	game->init("CSEngine", SDL_WINDOWS_CENTERED, SDL_WINDOWS_CENTERED, 800, 600, false);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}
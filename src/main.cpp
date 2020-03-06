#include "SDL.h"
#include "Game.h"
//#include <windows.h>

Game* game = nullptr;

int main(int argc, char *argv[])
{
	//Initializing FPS
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	//Initializing Game Engine
	game = new Game();
	game->init("NelEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, false);

	//Loop that loops if the game is running
	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		//Creating the frame delay
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	//Clean up
	game->clean();
	delete game;
	return 0;
}
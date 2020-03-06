#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include <stdlib.h>
#include <time.h>


Player* player;
GameObject* food;

GameObject* walls[80];

int Mcooldown;
int score = 1;
int maxCD = 10;

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}
Game::~Game()
{}

//Init function, this creates the window and the game
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) 
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}

		isRunning = true;

	}

	//Load player
	player = new Player(320, 320);
	srand(time(0));
	int gen1 = ((rand() % 18) * 32) + 32;
	srand(5);
	int gen2 = ((rand() % 18) * 32) + 32;
	food = new GameObject("assets/tileset.png",gen1, gen2,32,32);

	//generating walls
	for (int i = 0; i < 20; i++) {
		walls[i] = new GameObject("assets/tileset.png", i*32, 0, 64, 0);
 	}
	for (int i = 20; i < 40; i++) {
		walls[i] = new GameObject("assets/tileset.png", 0, (i - 20) * 32, 64, 0);
	}
	for (int i = 40; i < 60; i++) {
		walls[i] = new GameObject("assets/tileset.png", (i-40) * 32, 608, 64, 0);
	}
	for (int i = 60; i < 80; i++) {
		walls[i] = new GameObject("assets/tileset.png", 608, (i - 60) * 32, 64, 0);
	}
}

//Creates and deals with the events
void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				player->turn('w');
				break;
			case SDLK_RIGHT:
				player->turn('e');				
				break;
			case SDLK_UP:
				player->turn('n');
				break;
			case SDLK_DOWN:
				player->turn('s');
				break;
			}
			break;
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

//Updates the game every loop
void Game::update()
{


	if ((player->locX == food->xpos) && (player->locY == food->ypos)) {
		bool played = PlaySound(TEXT("assets/munch.wav"), NULL, SND_ASYNC);
		srand(time(0));
		food->xpos = ((rand() % 18) * 32) + 32;
		srand(time(0));
		food->ypos = ((rand() % 18) * 32) + 32;
		score++;
		std::cout << score << std::endl;
		player->incSize();
		if (score % 5 == 0) {
			maxCD = maxCD - 1;
		}
	}
	if (Mcooldown <= 0) {
		player->moveForward();
		Mcooldown = maxCD;

	}
	if (player->gameOver == true) {
		isRunning = false;
	}
	for (int i = 0; i < 80; i++) {
		walls[i]->Update();
	}

	for (int i = 0; i < 80; i++) {
		if ((player->locX == walls[i]->xpos) && (player->locY == walls[i]->ypos))
			isRunning = false;
	}
	if (isRunning == true) {
		player->Update();
	}
	food->Update();
	Mcooldown--;
	

}

//Render everything to the screen
void Game::render()
{
	SDL_RenderClear(renderer);
	for (int i = 0; i < 80; i++) {
		walls[i]->Render();
	}
	player->Render();
	food->Render();
	SDL_RenderPresent(renderer);
}

//Clean up everything going on
void Game::clean()
{
	delete player;
	delete food;
	for (int i = 0; i < 80; i++) {
		delete walls[i];
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}


#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y, int srcX, int srcY)
{

	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;

	srcRec.x = srcX;
	srcRec.y = srcY;
}

GameObject::~GameObject() {

}

void GameObject::Update()
{

	srcRec.h = 32;
	srcRec.w = 32;

	destRec.x = xpos;
	destRec.y = ypos;
	destRec.w = srcRec.w;
	destRec.h = srcRec.h;

}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRec, &destRec);
}

void GameObject::RenderEX(char c) {
	switch (c) {
	case 'n':
		SDL_RenderCopyEx(Game::renderer, objTexture, &srcRec, &destRec, 0, NULL, SDL_FLIP_NONE);
		break;
	case 'e':
		SDL_RenderCopyEx(Game::renderer, objTexture, &srcRec, &destRec, 90, NULL, SDL_FLIP_NONE);
		break;
	case 's':
		SDL_RenderCopyEx(Game::renderer, objTexture, &srcRec, &destRec, 180, NULL, SDL_FLIP_NONE);
		break;
	case 'w':
		SDL_RenderCopyEx(Game::renderer, objTexture, &srcRec, &destRec, 270, NULL, SDL_FLIP_NONE);
		break;
	}

}
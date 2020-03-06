#include "Game.h"


class GameObject {

public:
	GameObject(const char* texturesheet, int x, int y, int srcX, int srcY);
	~GameObject();

	void Update();
	void Render();
	void RenderEX(char facing);
	int xpos;
	int ypos;

private:



	SDL_Texture* objTexture;
	SDL_Rect srcRec, destRec;

};
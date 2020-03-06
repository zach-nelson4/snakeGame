#pragma once

#include "GameObject.h"
#include <vector>

class Player
{
public:
	Player(int x, int y);
	~Player();
	void moveForward();
	void turn(char t);
	void incSize();

	void Render();
	void Update();
	int spd = 32;
	bool gameOver = false;
	int locX;
	int locY;

private:

	char facing;
	GameObject* head;
	std::vector<GameObject*> body;
	GameObject* tail;

};


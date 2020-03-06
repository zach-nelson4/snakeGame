#include "Player.h"

//Constructor, Player consists of a head, a tail, and a body
Player::Player(int x, int y) {
	head = new GameObject("assets/tileset.png", x, y, 0, 0);
	tail = new GameObject("assets/tileset.png", x, y + 32, 0, 32);
	locX = x;
	locY = y;
	facing = 'n';
}

//Destructor, deletes the head, tail and body
Player::~Player() {
	delete head;
	for (int i = 0; i < body.size(); i++) {
		delete body[i];
	}
	delete tail;
}

//Renders the players head, body, and tail. Head and tail are based upon whichever way the snake is facing.
void Player::Render(){
	head->RenderEX(facing);
	for (unsigned i = 0; i < body.size(); i++) {
		body[i]->Render();
	}

	if (body.size() > 0) {
		if (body[body.size() - 1]->xpos > tail->xpos)
			tail->RenderEX('e');
		else if (body[body.size() - 1]->xpos < tail->xpos)
			tail->RenderEX('w');
		else if (body[body.size() - 1]->ypos > tail->ypos)
			tail->RenderEX('s');
		else
			tail->RenderEX('n');
	}
	else {
		if (head->xpos > tail->xpos)
			tail->RenderEX('e');
		else if (head->xpos < tail->xpos)
			tail->RenderEX('w');
		else if (head->ypos > tail->ypos)
			tail->RenderEX('s');
		else
			tail->RenderEX('n');
	}

}

//Updates everything
void Player::Update() {
	head->Update();
	for (unsigned i = 0; i < body.size(); i++) {
		body.at(i)->Update();
	}
	tail->Update();
}

//Increases the size of the snaek by one.
void Player::incSize() {

	GameObject* temp = new GameObject("assets/tileset.png", tail->xpos, tail->ypos, 32, 0);
	body.push_back(temp);
	temp = nullptr;
	switch (facing) {
	case 'n':
		tail->ypos = tail->ypos + 10;
		break;
	case 'w':
		tail->xpos = tail->xpos + 10;
		break;
	case 's':
		tail->ypos = tail->ypos - 10;
		break;
	case 'e':
		tail->xpos = tail->xpos - 10;
		break;
	}
}

//Moves the snake forward by one unit.
void Player::moveForward() {

	
	if (body.size() > 0) {
		tail->ypos = body[body.size() - 1]->ypos;
		tail->xpos = body[body.size() - 1]->xpos;

		for (int i = body.size() - 1; i > 0; i--) {
			body[i]->xpos = body[i - 1]->xpos;
			body[i]->ypos = body[i - 1]->ypos;
		}

		body[0]->ypos = head->ypos;
		body[0]->xpos = head->xpos;

	}
	else {
		tail->ypos = head->ypos;
		tail->xpos = head->xpos;
	}

	switch (facing) {

		//Facing North
	case 'n':
		head->ypos = head->ypos - spd;
		locY -= 32;
		break;

		//Facing West
	case 'w':
		head->xpos = head->xpos - spd;
		locX -= 32;
		break;
		
		//Facing South
	case 's':
		head->ypos = head->ypos + spd;
		locY += 32;
		break;

		//Facing East
	case 'e':
		head->xpos = head->xpos + spd;
		locX += 32;
		break;
	}
	
	if (body.size() > 0) {
		for (size_t i = 0; i < body.size(); i++) {
			if ((head->xpos == body[i]->xpos) && (head->ypos == body[i]->ypos)) {
				gameOver = true;
				break;
			}
		}
	}
}

//Turns the snake the direction given by t.
void Player::turn(char t) {
	switch (facing) {
	case 'e':
		if (t != 'w')		
			facing = t;
		break;
	case 'w':
		if (t != 'e')
			facing = t;
		break;
	case 'n':
		if (t != 's')
			facing = t;
		break;
	case 's':
		if (t != 'n')
			facing = t;
		break;
	}
}
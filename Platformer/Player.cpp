/**********************************************************************************
// Player (Código Fonte)
//
// Criação:     20 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para o jogador
//
**********************************************************************************/

#include "Player.h"
#include "Bomb.h"
#include "BombZombie.h"

// ---------------------------------------------------------------------------------

Player::Player(GridSet** gridSet)
{
	tileset = new TileSet("Resources/player.png", 40, 40, 3, 12);
	anim = new Animation(tileset, 0.15f, true);
	gridI = 0;
	gridJ = 0;
	gridIndex = 0;

	uint DownMove[2] = { 0, 2 };
	uint DownIdle[1] = { 1 };

	uint LeftMove[2] = { 3, 5 };
	uint LeftIdle[1] = { 4 };

	uint RightMove[2] = { 6, 8 };
	uint RightIdle[1] = { 7 };

	uint TopMove[2] = { 9, 11 };
	uint TopIdle[1] = { 10 };

	anim->Add(DOWN_MOVE, DownMove, 2);
	anim->Add(DOWN_IDLE, DownIdle, 1);

	anim->Add(LEFT_MOVE, LeftMove, 2);
	anim->Add(LEFT_IDLE, LeftIdle, 1);

	anim->Add(RIGHT_MOVE, RightMove, 2);
	anim->Add(RIGHT_IDLE, RightIdle, 1);

	anim->Add(TOP_MOVE, TopMove, 2);
	anim->Add(TOP_IDLE, TopIdle, 1);

	float x1 = -20.0f;
	float y1 = -20.0f;
	float x2 = 20.0f;
	float y2 = 20.0f;

	BBox(new Rect(x1, y1, x2, y2));

	state = DOWN_IDLE;
	spcCtrl = true;
	shootCtrl = true;
	type = PLAYER;
	bombPlanted = false;
	this->gridSet = gridSet;

	hp = 3;
	bombSize = 7;

	MoveTo(30.0f, 130.0f, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete tileset;
	delete anim;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
	if (obj->Type() == BOMB)
		bombPlanted = true;
	else
		bombPlanted = false;

	if (obj->Type() == GRID) {
		float objLft = obj->X() - 20.0f;
		float objRgt = obj->X() + 20.0f;
		float objTop = obj->Y() - 20.0f;
		float objBot = obj->Y() + 20.0f;

		if (x >= objLft && x <= objRgt && y >= objTop && y <= objBot) {

			GridSet* grid = (GridSet*)obj;
			gridI = grid->i;
			gridJ = grid->j;
			gridIndex = grid->index;
		}
	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	if (x < 30.0f)
		MoveTo(30.0f, y);
	if (y < 130)
		MoveTo(x, 130.0f);
	if (x + 20 > 530)
		MoveTo(510.0f, y);
	if (y + 20 > 630)
		MoveTo(x, 610.0f);

	if (window->KeyDown(VK_UP) || window->KeyDown('W') && gridSet[gridIndex - 13]->Type() == GRID) {
		Translate(0, -160.0f * gameTime);
		state = TOP_MOVE;
	}
	else if (window->KeyDown(VK_RIGHT) || window->KeyDown('D') && gridSet[gridIndex + 1]->Type() == GRID) {
		Translate(160.0f * gameTime, 0);
		state = RIGHT_MOVE;
	}
	else if (window->KeyDown(VK_LEFT) || window->KeyDown('A') && gridSet[gridIndex - 1]->Type() == GRID) {
		Translate(-160.0f * gameTime, 0);
		state = LEFT_MOVE;
	}
	else if (window->KeyDown(VK_DOWN) || window->KeyDown('S') && gridSet[gridIndex + 13]->Type() == GRID) {
		Translate(0, 160.0f * gameTime);
		state = DOWN_MOVE;
	}

	if (spcCtrl && window->KeyDown(VK_SPACE)) {
		score++;
		spcCtrl = false;
	}
	else if (window->KeyUp(VK_SPACE))
		spcCtrl = true;

	//soltar bomba
	if (!bombPlanted && shootCtrl && window->KeyDown('Z') || window->KeyDown('K')) {

		Bomb* b = new Bomb(bombSize, 30.0f + (40.0f * gridI), 130.0f + (40.0f * gridJ));
		BombZombie::scene->Add(b, MOVING);
		shootCtrl = false;
	}
	else if (window->KeyUp('Z') && window->KeyUp('K'))
		shootCtrl = true;


	if ((window->KeyUp(VK_DOWN) && window->KeyUp('S')) &&
		(window->KeyUp(VK_UP) && window->KeyUp('W')) &&
		(window->KeyUp(VK_LEFT) && window->KeyUp('A')) &&
		(window->KeyUp(VK_RIGHT) && window->KeyUp('D'))) {
		switch (state)
		{
		case DOWN_MOVE:
			state = DOWN_IDLE;
			break;
		case TOP_MOVE:
			state = TOP_IDLE;
			break;
		case LEFT_MOVE:
			state = LEFT_IDLE;
			break;
		case RIGHT_MOVE:
			state = RIGHT_IDLE;
			break;
		}
	}

	/*

	 if (hp == 2)
	 {
		 BombZombie::scene->Delete(h3, STATIC);
	 }
	 else if (hp == 1)
	 {
		 BombZombie::scene->Delete(h2, STATIC);
	 }
	 else
	 {
		 BombZombie::scene->Delete(h1, STATIC);
	 }
	*/

	anim->Select(state);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------
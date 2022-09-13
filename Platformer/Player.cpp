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

Player::Player()
{
	tileset = new TileSet("Resources/player.png", 27, 32, 3, 12);
	anim = new Animation(tileset, 0.15f, true);


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

	float x1 = -15.0f;
	float y1 = -16.0f;
	float x2 = 15.0f;
	float y2 = 16.0f;

	BBox(new Rect(x1, y1, x2, y2));

	state = DOWN_IDLE;
	spcCtrl = true;
	shootCtrl = true;
	type = PLAYER;

	hp = 3;
	bombSize = 5;

	MoveTo(30.0f, 130.0f, 0.0f);
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
	float plyRgt = x + 15;
	float plyLft = x - 15;
	float plyTop = y - 16;
	float plyBot = y + 16;

	float pivRgt;
	float pivLft;
	float pivTop;
	float pivBot;

	if (obj->Type() == PIVOT) {
		Pivot* pivot = (Pivot*)obj;

		pivTop = pivot->Y() - 20;
		pivBot = pivot->Y() + 20;
		pivLft = pivot->X() - 20;
		pivRgt = pivot->X() + 20;

		float leftDif = pivLft - plyLft;
		float rightDif = plyRgt - pivRgt;
		float topDif = plyBot - pivTop;
		float botDif = pivBot - plyTop;

		//left-top
		if (leftDif > 0 && topDif < 5)
			MoveTo(x, pivTop - 16);
		//right-top
		else if (rightDif > 0 && topDif < 5)
			MoveTo(x, pivTop - 16);
		//left-bot
		else if (leftDif > 0 && botDif < 5)
			MoveTo(x, pivBot + 16);
		//right-bot
		else if (rightDif > 0 && botDif < 5)
			MoveTo(x, pivBot + 16);
		//left
		else if (leftDif > 0 && topDif >= 5)
			MoveTo(pivLft - 16, y);
		//right
		else if (rightDif > 0 && topDif >= 5)
			MoveTo(pivRgt + 16, y);
		//top
		else if (leftDif < 0 && topDif < 5)
			MoveTo(x, pivTop - 16);
		//bot
		else if (leftDif < 0 && botDif < 5)
			MoveTo(x, pivBot + 16);

	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	if (x < 25.0f)
		MoveTo(25.0f, y);
	if (y < 126)
		MoveTo(x, 126.0f);
	if (x + 15 > 370)
		MoveTo(355.0f, y);
	if (y + 16 > 470)
		MoveTo(x, 454.0f);

	if (window->KeyDown(VK_UP) || window->KeyDown('W')) {
		Translate(0, -160.0f * gameTime);
		state = TOP_MOVE;
	}
	else if (window->KeyDown(VK_RIGHT) || window->KeyDown('D')) {
		Translate(160.0f * gameTime, 0);
		state = RIGHT_MOVE;
	}
	else if (window->KeyDown(VK_LEFT) || window->KeyDown('A')) {
		Translate(-160.0f * gameTime, 0);
		state = LEFT_MOVE;
	}
	else if (window->KeyDown(VK_DOWN) || window->KeyDown('S')) {
		Translate(0, 160.0f * gameTime);
		state = DOWN_MOVE;
	}

	if (spcCtrl && window->KeyDown(VK_SPACE)) {
		hp--;
		spcCtrl = false;
	}
	else if (window->KeyUp(VK_SPACE))
		spcCtrl = true;

	//soltar bomba
	if (shootCtrl && window->KeyDown('Z') || window->KeyDown('K')) {

		Bomb* b = new Bomb(bombSize, x, y);
		BombZombie::scene->Add(b, STATIC);
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
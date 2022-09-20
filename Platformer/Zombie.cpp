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

#include "Zombie.h"
#include "Player.h"
#include "GridSet.h"
#include "Scene.h"
#include "BombZombie.h"

// ---------------------------------------------------------------------------------

Zombie::Zombie(Player* player, GridSet** gridSet, uint i, uint j)
{
	tileset = new TileSet("Resources/zombie.png", 40, 40, 3, 12);
	anim = new Animation(tileset, 0.15f, true);
	this->player = player;

	right = false;
	left = false;
	top = false;
	down = false;

	gridI = i;
	gridJ = j;

	uint DownMove[2] = { 0, 2 };
	uint DownIdle[1] = { 1 };

	uint LeftMove[2] = { 3, 5 };
	uint LeftIdle[1] = { 4 };

	uint RightMove[2] = { 6, 8 };
	uint RightIdle[1] = { 7 };

	uint TopMove[2] = { 9, 11 };
	uint TopIdle[1] = { 10 };

	anim->Add(DWN_MOVE, DownMove, 2);
	anim->Add(DWN_IDLE, DownIdle, 1);

	anim->Add(LFT_MOVE, LeftMove, 2);
	anim->Add(LFT_IDLE, LeftIdle, 1);

	anim->Add(RGT_MOVE, RightMove, 2);
	anim->Add(RGT_IDLE, RightIdle, 1);

	anim->Add(TP_MOVE, TopMove, 2);
	anim->Add(TP_IDLE, TopIdle, 1);

	float x1 = -20.0f;
	float y1 = -20.0f;
	float x2 = 20.0f;
	float y2 = 20.0f;

	BBox(new Rect(x1, y1, x2, y2));

	state = DWN_IDLE;
	type = ZOMBIE;
	this->gridSet = gridSet;

	hp = 2;

	MoveTo(30.0f + (40.0f * i), 130.0f + (40.0f * j), Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Zombie::~Zombie()
{
	delete tileset;
	delete anim;
}

// ---------------------------------------------------------------------------------

void Zombie::OnCollision(Object* obj)
{
	float plyLft = x - 20.0f;
	float plyRgt = x + 20.0f;
	float plyTop = y - 20.0f;
	float plyBot = y + 20.0f;


	float objLft = obj->X() - 20.0f;
	float objRgt = obj->X() + 20.0f;
	float objTop = obj->Y() - 20.0f;
	float objBot = obj->Y() + 20.0f;

	float topDiff = plyTop - objTop;
	float botDiff = plyBot - objBot;
	float rgtDiff = plyRgt - objRgt;
	float lftDiff = plyLft - objLft;

	if (topDiff < 0)
		topDiff = -topDiff;
	if (botDiff < 0)
		botDiff = -botDiff;
	if (lftDiff < 0)
		lftDiff = -lftDiff;
	if (rgtDiff < 0)
		rgtDiff = -rgtDiff;

	if (obj->Type() == EXPLOSION) {
		if ((lftDiff <= 35.0f && rgtDiff <= 35.0f) && (topDiff <= 35.0f && botDiff <= 35.0f)) {
			player->score += 100;
			BombZombie::zombiesLeft--;
			BombZombie::scene->Delete(this, MOVING);
		}
	}

	if (obj->Type() == OBSTACLE || obj->Type() == PIVOT) {

		//right
		if (plyRgt >= objLft && plyLft < objLft && topDiff <= 30.0f && botDiff <= 30.0f) {
			MoveTo(obj->X() - 40.0f, y);
			right = true;
		}

		//left
		if (plyLft <= objRgt && plyRgt > objRgt && topDiff <= 30.0f && botDiff <= 30.0f) {
			MoveTo(obj->X() + 40.0f, y);
			left = true;
		}

		//top
		if (plyTop <= objBot && plyBot > objBot && lftDiff <= 30.0f && rgtDiff <= 30.0f) {
			MoveTo(x, obj->Y() + 40.0f);
			top = true;
		}

		//down
		if (plyBot >= objTop && plyTop < objTop && lftDiff <= 30.0f && rgtDiff <= 30.0f) {
			MoveTo(x, obj->Y() - 40.0f);
			down = true;
		}
	}

	if (obj->Type() == ZOMBIE) {

		//right
		if (plyRgt >= objLft && plyLft < objLft && topDiff <= 30.0f && botDiff <= 30.0f) {
			MoveTo(obj->X() - 40.0f, y);
			right = true;
		}

		//left
		if (plyLft <= objRgt && plyRgt > objRgt && topDiff <= 30.0f && botDiff <= 30.0f) {
			MoveTo(obj->X() + 40.0f, y);
			left = true;
		}

		//top
		if (plyTop <= objBot && plyBot > objBot && lftDiff <= 30.0f && rgtDiff <= 30.0f) {
			MoveTo(x, obj->Y() + 40.0f);
			top = true;
		}

		//down
		if (plyBot >= objTop && plyTop < objTop && lftDiff <= 30.0f && rgtDiff <= 30.0f) {
			MoveTo(x, obj->Y() - 40.0f);
			down = true;
		}
	}



	if (obj->Type() == BOMB) {
		Bomb* b = (Bomb*)obj;

		if (b->instance >= 2) {
			//right
			if (plyRgt >= objLft && plyLft < objLft && topDiff <= 35.0f && botDiff <= 35.0f) {
				right = true;
			}

			//left
			if (plyLft <= objRgt && plyRgt > objRgt && topDiff <= 35.0f && botDiff <= 35.0f) {
				left = true;
			}

			//top
			if (plyTop <= objBot && plyBot > objBot && lftDiff <= 35.0f && rgtDiff <= 35.0f) {
				top = true;
			}

			//down
			if (plyBot >= objTop && plyTop < objTop && lftDiff <= 35.0f && rgtDiff <= 35.0f) {
				down = true;
			}
		}
	}

	if (obj->Type() == GRID) {

		if (topDiff <= 10.0f && botDiff <= 10.0f && lftDiff <= 10.0f && rgtDiff <= 10.0f) {

			GridSet* grid = (GridSet*)obj;

			gridI = grid->i;
			gridJ = grid->j;
			gridIndex = grid->index;

		}
	}
}

// ---------------------------------------------------------------------------------

void Zombie::Update()
{
	// ---------------------------------------------------------------------------------
	//verificação dos limites do mapa
	if (x < 30.0f)
		MoveTo(30.0f, y);

	if (y < 130.0f)
		MoveTo(x, 130.0f);

	if (x + 20 > 530.0f)
		MoveTo(510.0f, y);

	if (y + 20 > 630.0f)
		MoveTo(x, 610.0f);


	// ---------------------------------------------------------------------------------
	//IA zombie


	if (top && right && down && left) {
		state = DOWN_MOVE;
	}

	// ---------------------------------------------------------------------------------
	//Down / Top
	else if ((gridI >= player->gridI) && (gridJ > player->gridJ) && (leftTemp)) {

		Translate(40.0f * gameTime, 0);
		state = RGT_MOVE;

		if (!top)
		{
			leftTemp = false;
		}

	}
	else if ((gridI <= player->gridI) && (gridJ > player->gridJ) && (rightTemp)) {
		Translate(-40.0f * gameTime, 0);
		state = LFT_MOVE;

		if (!top)
		{
			rightTemp = false;
		}

	}

	else if ((gridI <= player->gridI) && (gridJ < player->gridJ) && (rightTemp)) {

		Translate(-40.0f * gameTime, 0);
		state = LFT_MOVE;

		if (!down)
		{
			rightTemp = false;
		}

	}

	else if ((gridI >= player->gridI) && (gridJ < player->gridJ) && (leftTemp)) {

		Translate(40.0f * gameTime, 0);
		state = RGT_MOVE;

		if (!down)
		{
			leftTemp = false;
		}

	}

	// ---------------------------------------------------------------------------------
	//Right / Left




	// ---------------------------------------------------------------------------------




	else if (gridJ > player->gridJ) {

		if (top == true)
		{
			if (right == false) {

				Translate(0, -40.0f * gameTime);
				state = TP_MOVE;
				rightTemp = true;

			}
			else if (left == false) {

				Translate(0, -40.0f * gameTime);
				state = TP_MOVE;
				leftTemp = true;
			}
		}
		else
		{
			Translate(0, -40.0f * gameTime);
			state = TP_MOVE;
			leftTemp = false;
			rightTemp = false;


		}

	}

	else if (gridJ < player->gridJ) {

		if (down == true)
		{
			if (right == false) {
				Translate(40.0f * gameTime, 0);
				state = RGT_MOVE;
				rightTemp = true;
			}
			else if (left == false) {
				Translate(-40.0f * gameTime, 0);
				state = LFT_MOVE;
				leftTemp = true;

			}
		}
		else
		{
			Translate(0, 40.0f * gameTime);
			state = DWN_MOVE;
			leftTemp = false;
			rightTemp = false;
		}
	}

	else if (gridI > player->gridI)
	{
		if (left == true)
		{
			if (top == false)
			{
				Translate(0, -40.0f * gameTime);
				state = TP_MOVE;
				topTemp = true;
			}

			else if (down == false) {
				Translate(0, 40.0f * gameTime);
				state = DWN_MOVE;
				downTemp = true;


			}
		}
		else {
			Translate(-40.0f * gameTime, 0);
			state = LFT_MOVE;
			topTemp = false;
			downTemp = false;

		}

	}

	else if (gridI < player->gridI)
	{
		if (right == true)
		{
			if (top == false)
			{
				Translate(0, -40.0f * gameTime);
				state = TP_MOVE;
				topTemp = true;

			}
			else if (down == false) {

				Translate(0, 40.0f * gameTime);
				state = DWN_MOVE;
				downTemp = true;

			}
		}
		else {
			Translate(40.0f * gameTime, 0);
			state = RGT_MOVE;
			topTemp = false;
			downTemp = false;
		}

	}

	top = false;
	right = false;
	left = false;
	down = false;

	anim->Select(state);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------
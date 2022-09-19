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

Zombie::Zombie(Player* player, GridSet** gridSet)
{
	tileset = new TileSet("Resources/player.png", 40, 40, 3, 12);
	anim = new Animation(tileset, 0.15f, true);
	this->player = player;

	gridI = 0;
	gridJ = 0;
	gridIndex = 0;

	right = false;
	left = false;
	top = false;
	down = false;


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

	MoveTo(window->CenterX(), window->CenterY() - 28, Layer::MIDDLE);
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

	if (obj->Type() == OBSTACLE || obj->Type() == PIVOT) {

		//right
		if (plyRgt >= objLft && plyLft < objLft && topDiff <= 35.0f && botDiff <= 35.0f) {
			MoveTo(obj->X() - 40.0f, y);
			right = false;
		}

		//left
		if (plyLft <= objRgt && plyRgt > objRgt && topDiff <= 35.0f && botDiff <= 35.0f) {
			MoveTo(obj->X() + 40.0f, y);
			left = false;
		}

		//top
		if (plyTop <= objBot && plyBot > objBot && lftDiff <= 35.0f && rgtDiff <= 35.0f) {
			MoveTo(x, obj->Y() + 40.0f);
			top = false;
		}

		//down
		if (plyBot >= objTop && plyTop < objTop && lftDiff <= 35.0f && rgtDiff <= 35.0f) {
			MoveTo(x, obj->Y() - 40.0f);
			down = false;
		}
	}

	if (obj->Type() == BOMB) {
		Bomb* b = (Bomb*)obj;

		if (b->instance >= 2) {
			//right
			if (plyRgt >= objLft && plyLft < objLft && topDiff <= 35.0f && botDiff <= 35.0f) {
				right = false;
			}

			//left
			if (plyLft <= objRgt && plyRgt > objRgt && topDiff <= 35.0f && botDiff <= 35.0f) {
				left = false;
			}

			//top
			if (plyTop <= objBot && plyBot > objBot && lftDiff <= 35.0f && rgtDiff <= 35.0f) {
				top = false;
			}

			//down
			if (plyBot >= objTop && plyTop < objTop && lftDiff <= 35.0f && rgtDiff <= 35.0f) {
				down = false;
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

	if (obj->Type() == EXPLOSION) {
		if (lftDiff <= 39.0f && topDiff <= 39.0f) {
			player->score++;
			BombZombie::scene->Delete(this, MOVING);
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
		MoveTo(530.0f, y);

	if (y + 20 > 630.0f) 
		MoveTo(x, 630.0f);


	if (gridI > player->gridI)
	{
		if (left == true)
		{
			if (top == false)
			{
				while (gridJ > (gridJ + 1))
				{
					Translate(0, -100.0f * gameTime);
					state = TP_MOVE;
				}

				Translate(-100.0f * gameTime, 0);
				state = LFT_MOVE;
			}
			else if (down == false) {

				while (gridJ > (gridJ + 1))
				{
					Translate(0, 100.0f * gameTime);
					state = DWN_MOVE;
				}

				Translate(-100.0f * gameTime, 0);
				state = LFT_MOVE;

			}
		}
		else {
			Translate(-100.0f * gameTime, 0);
			state = LFT_MOVE;
		}

	}
	else if (gridJ > player->gridJ) {

		if (top == true)
		{
			if (right == false) {
				while (gridI > (gridI + 1))
				{
					Translate(100.0f * gameTime, 0);
					state = RGT_MOVE;
				}
				Translate(0, -100.0f * gameTime);
				state = TP_MOVE;

			}
			else if (left == false) {
				while (gridI > (gridI + 1))
				{
					Translate(-100.0f * gameTime, 0);
					state = LFT_MOVE;
				}
				Translate(0, -100.0f * gameTime);
				state = TP_MOVE;
			}
		}
		else
		{
			Translate(0, -100.0f * gameTime);
			state = TP_MOVE;
		}

	}
	else if (gridI < player->gridI)
	{
		if (right == true)
		{
			if (top == false)
			{
				while (gridJ > (gridJ + 1))
				{
					Translate(0, -100.0f * gameTime);
					state = TP_MOVE;
				}

				Translate(100.0f * gameTime, 0);
				state = RGT_MOVE;
			}
			else if (down == false) {

				while (gridJ > (gridJ + 1))
				{
					Translate(0, 100.0f * gameTime);
					state = DWN_MOVE;
				}

				Translate(100.0f * gameTime, 0);
				state = RGT_MOVE;

			}
		}
		else {
			Translate(100.0f * gameTime, 0);
			state = RGT_MOVE;
		}

	}
	else if (gridJ < player->gridJ) {

		if (down == true)
		{
			if (right == false) {
				while (gridI > (gridI + 1))
				{
					Translate(100.0f * gameTime, 0);
					state = RGT_MOVE;
				}
				Translate(0, 100.0f * gameTime);
				state = DWN_MOVE;

			}
			else if (left == false) {
				while (gridI > (gridI + 1))
				{
					Translate(-100.0f * gameTime, 0);
					state = LFT_MOVE;
				}
				Translate(0, 100.0f * gameTime);
				state = DWN_MOVE;
			}
		}
		else
		{
			Translate(0, 100.0f * gameTime);
			state = DWN_MOVE;
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
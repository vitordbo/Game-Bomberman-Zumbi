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

// ---------------------------------------------------------------------------------

Zombie::Zombie(Player* player, GridSet** gridSet)
{
	tileset = new TileSet("Resources/player.png", 40, 40, 3, 12);
	anim = new Animation(tileset, 0.15f, true);
	this->player = player;
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

	MoveTo(window->CenterX(), window->CenterY() - 10, Layer::MIDDLE);
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
	float plyRgt = x + 15;
	float plyLft = x - 15;
	float plyTop = y - 16;
	float plyBot = y + 16;

	float pivRgt;
	float pivLft;
	float pivTop;
	float pivBot;

	if (obj->Type() == GRID) {

		/* Calcula a diferença de distancia do centro do
		player e do grid (é utilizado o módulo do valor!!!)*/

		float xDiff = x - obj->X() > 0 ? x - obj->X() : -(x - obj->X());
		float yDiff = y - obj->Y() > 0 ? y - obj->Y() : -(y - obj->Y());

		if (xDiff <= 10.0f && yDiff <= 10.0f) {
			GridSet* grid = (GridSet*)obj;
			gridI = grid->i;
			gridJ = grid->j;
			gridIndex = grid->index;
		}
	}

	if (obj->Type() == PIVOT || obj->Type() == OBSTACLE) {
		GridSet* pivot = (GridSet*)obj;

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

void Zombie::Update()
{
	if (x < 25)
		MoveTo(25.0f, y);
	if (y < 126)
		MoveTo(x, 126.0f);
	if (x + 15 > 370)
		MoveTo(355.0f, y);
	if (y + 16 > 470)
		MoveTo(x, 454.0f);

	if (distanceX() > 0 && distanceX() < 50.0f)
	{
		Translate(-100.0f * gameTime, 0);
		state = LFT_MOVE;
	}
	else if (distanceY() > 0 && distanceY() < 50.0f)
	{
		Translate(0, -100.0f * gameTime);
		state = TP_MOVE;
	}
	else if (distanceX() < 0 && distanceX() < 50.0f)
	{
		Translate(100.0f * gameTime, 0);
		state = RGT_MOVE;
	}
	else if (distanceY() < 0 && distanceY() < 50.0f)
	{
		Translate(0, 100.0f * gameTime);
		state = DWN_MOVE;
	}

	anim->Select(state);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------
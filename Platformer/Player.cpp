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
#include "BombZombie.h"

// ---------------------------------------------------------------------------------

Player::Player(GridSet** gridSet)
{
	tileset = new TileSet("Resources/player.png", 40, 40, 3, 12);
	anim = new Animation(tileset, 0.15f, true);
	gridI = 0;
	gridJ = 0;
	gridIndex = 1;

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
	
	immune = false;
	score = 0;

	hp = 3;
	bombSize = 7;
	bombsLeft = 2;

	top = true;
	left = true;
	right = true;
	down = true;

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
	
	float plyLft  = x - 20.0f;
	float plyRgt = x + 20.0f;
	float plyTop  = y - 20.0f;
	float plyBot  = y + 20.0f;

	
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

	if (obj->Type() == BOMB)
		bombPlanted = true;
	else
		bombPlanted = false;

	if (obj->Type() == GRID) {
		
		if (topDiff < 5.0f && botDiff < 5.0f && lftDiff < 5.0f && rgtDiff < 5.0f) {

			GridSet* grid = (GridSet*)obj;

			if ((window->KeyUp(VK_DOWN) && window->KeyUp('S')) &&
				(window->KeyUp(VK_UP) && window->KeyUp('W')) &&
				(window->KeyUp(VK_LEFT) && window->KeyUp('A')) &&
				(window->KeyUp(VK_RIGHT) && window->KeyUp('D'))) {

				MoveTo(obj->X(), obj->Y());
			}

			gridI = grid->i;
			gridJ = grid->j;
			gridIndex = grid->index;

			//testade posição novamente após ter ajustado o personagem
			if (topDiff < 5.0f && botDiff < 5.0f && lftDiff < 5.0f && rgtDiff < 5.0f) {
				top = true;
				left = true;
				right = true;
				down = true;
			}
			else {
				if (top || down) {
					left = false;
					right = false;
				}
				else if (left || right) {
					top = false;
					right = false;
				}

			}
		}
		
	}
	if(obj->Type() == EXPLOSION && !immune){
		if (lftDiff < 38.0f && topDiff < 38.0f) {
			hp--;
			MoveTo(30.0f, 130.0f);
			immune = true;
		}
	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	Immune();

	//limites do mapa
	if (x <= 30.0f) {
		if ((window->KeyDown(VK_LEFT) || window->KeyDown('A')))
			state = LEFT_MOVE;
		leftLimit = false;
	}
	else
		leftLimit = true;

	if (y <= 130) {
		if ((window->KeyDown(VK_UP) || window->KeyDown('W')))
			state = TOP_MOVE;
		topLimit = false;
	}
	else
		topLimit = true;

	if (x + 20 >= 530) {
		if ((window->KeyDown(VK_RIGHT) || window->KeyDown('D')))
			state = RIGHT_MOVE;
		rightLimit = false;
	}
	else
		rightLimit = true;

	if (y + 20 >= 630) {
		if ((window->KeyDown(VK_DOWN) || window->KeyDown('S')))
			state = DOWN_MOVE;
		downLimit = false;
	}
	else
		downLimit = true;

	//movimentação
	
	//top
	if (gridIndex >= 13) {
		if (top && topLimit && gridSet[gridIndex - 13]->Type() == GRID && (window->KeyDown(VK_UP) || window->KeyDown('W'))) {
			MoveTo(x, y - 1.0f);
			state = TOP_MOVE;
		}
	}

	//right
	if (gridIndex + 1 < 169) {
		if (right && rightLimit && gridSet[gridIndex + 1]->Type() == GRID && (window->KeyDown(VK_RIGHT) || window->KeyDown('D'))) {
			MoveTo(x + 1.0f, y);
			state = RIGHT_MOVE;
		}
	}
	
	//left
	if (gridIndex >= 1) {
		if (left && leftLimit && gridSet[gridIndex - 1]->Type() == GRID && (window->KeyDown(VK_LEFT) || window->KeyDown('A'))) {
			MoveTo(x - 1.0f, y);
			state = LEFT_MOVE;
		}
	}
	
	//down
	if (gridIndex + 13 < 169) {
		if (down && downLimit && gridSet[gridIndex + 13]->Type() == GRID && (window->KeyDown(VK_DOWN) || window->KeyDown('S'))) {
			MoveTo(x, y + 1.0f);
			state = DOWN_MOVE;
		}
	}
	
	//espaço
	if (spcCtrl && window->KeyDown(VK_SPACE)) {
		score++;
		spcCtrl = false;
	}
	else if (window->KeyUp(VK_SPACE))
		spcCtrl = true;

	//soltar bomba
	if (!bombPlanted && bombsLeft > 0 && shootCtrl && window->KeyDown('Z') || window->KeyDown('K')) {

		Bomb * bomb = new Bomb(bombSize, 30.0f + (40.0f * gridI), 130.0f + (40.0f * gridJ));
		BombZombie::scene->Add(bomb, MOVING);
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

	anim->Select(state);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------
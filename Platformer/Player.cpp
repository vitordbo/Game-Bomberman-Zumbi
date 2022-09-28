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
	initialIndex = 0;
	stopped = false;

	uint DownMove[3] = { 0, 1, 2 };
	uint DownIdle[1] = { 1 };

	uint LeftMove[3] = { 3, 4, 5 };
	uint LeftIdle[1] = { 4 };

	uint RightMove[3] = { 6, 7, 8 };
	uint RightIdle[1] = { 7 };

	uint TopMove[3] = { 9, 10, 11 };
	uint TopIdle[1] = { 10 };

	anim->Add(DOWN_MOVE, DownMove, 3);
	anim->Add(DOWN_IDLE, DownIdle, 1);

	anim->Add(LEFT_MOVE, LeftMove, 3);
	anim->Add(LEFT_IDLE, LeftIdle, 1);

	anim->Add(RIGHT_MOVE, RightMove, 3);
	anim->Add(RIGHT_IDLE, RightIdle, 1);

	anim->Add(TOP_MOVE, TopMove, 3);
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
	bombSize = 2;
	bombsMax = 1;
	bombsLeft = 1;
	velocity = 100.0f;

	top = false;
	left = false;
	right = true;
	down = true;

	topLimit = false;
	leftLimit = false;
	rightLimit = true;
	downLimit = true;
	doorReached = false;

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

	if (obj->Type() == EXPLOSION && !immune) {
		if ((lftDiff <= 35.0f && rgtDiff <= 35.0f) && (topDiff <= 35.0f && botDiff <= 35.0f)) {
			hp--;
			MoveTo(30.0f, 130.0f);
			immune = true;
			stopped = true;
		}
	}
	else {
		if (obj->Type() == ZOMBIE && !immune) {
			if ((lftDiff <= 10.0f && rgtDiff <= 10.0f) && (topDiff <= 10.0f && botDiff <= 10.0f)) {
				hp--;
				MoveTo(30.0f, 130.0f);
				immune = true;
				stopped = true;
			}
		}

		if (obj->Type() == OBSTACLE || obj->Type() == PIVOT) {

			//right
			if (plyRgt >= objLft && plyLft < objLft && topDiff <= 30.0f && botDiff <= 30.0f) {
				MoveTo(obj->X() - 40.0f, y);
				right = false;
			}

			//left
			if (plyLft <= objRgt && plyRgt > objRgt && topDiff <= 30.0f && botDiff <= 30.0f) {
				MoveTo(obj->X() + 40.0f, y);
				left = false;
			}

			//top
			if (plyTop <= objBot && plyBot > objBot && lftDiff <= 30.0f && rgtDiff <= 30.0f) {
				MoveTo(x, obj->Y() + 40.0f);
				top = false;
			}

			//down
			if (plyBot >= objTop && plyTop < objTop && lftDiff <= 30.0f && rgtDiff <= 30.0f) {
				MoveTo(x, obj->Y() - 40.0f);
				down = false;
			}
		}

		if (obj->Type() == BOMB) {
			Bomb* b = (Bomb*)obj;

			bombPlanted = true;

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

				if (initialIndex != gridIndex) {
					initialIndex = gridIndex;

					if (grid->objPosExp == 2) {
						if (hp < 3)
							hp++;

						grid->objPosExp = 0;
					}
					else if (grid->objPosExp == 3) {
						bombsMax++;
						bombsLeft++;

						grid->objPosExp = 0;
					}
					else if (grid->objPosExp == 4) {
						bombSize++;

						grid->objPosExp = 0;
					}
				}

			}
		}
	}	
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	//verifica se o jogador está posicionado em uma porta
	if (gridSet[gridIndex]->objPosExp == 1)
		doorReached = true;
	else
		doorReached = false;

	if (bombsLeft > bombsMax)
		bombsLeft = bombsMax;

	Immune();

	//movimentação

	// ---------------------------------------------------------------------------------
	//verificação dos limites do mapa
	if (x < 30.0f) {
		MoveTo(30.0f, y);
		leftLimit = false;
	}
	else
		leftLimit = true;

	if (y < 130.0f){
		MoveTo(x, 130.0f);
		topLimit = false;
	}
	else
		topLimit = true;

	if (x + 20 > 530.0f) {
		MoveTo(510.0f, y);
		rightLimit = false;
	}
	else
		rightLimit = true;

	if (y + 20 > 630.0f) {
		MoveTo(x, 610.0f);
		downLimit = false;
	}
	else
		downLimit = true;

	// ---------------------------------------------------------------------------------
	//animação
	if (window->KeyDown(VK_UP) || window->KeyDown('W')) {
		state = TOP_MOVE;
	}
	else if (window->KeyDown(VK_RIGHT) || window->KeyDown('D')) {
		state = RIGHT_MOVE;
		}
	else if (window->KeyDown(VK_LEFT) || window->KeyDown('A')) {
		state = LEFT_MOVE;
	}
	else if (window->KeyDown(VK_DOWN) || window->KeyDown('S')) {
		state = DOWN_MOVE;
	}
	
	// ---------------------------------------------------------------------------------
	//detecção de teclas
	
	if (!stopped) {
		//top
		if (topLimit && top && (window->KeyDown(VK_UP) || window->KeyDown('W')))
			Translate(0, -(velocity) * gameTime);

		//right
		if (rightLimit && right && (window->KeyDown(VK_RIGHT) || window->KeyDown('D')))
			Translate(velocity * gameTime, 0);

		//left
		if (leftLimit && left && (window->KeyDown(VK_LEFT) || window->KeyDown('A')))
			Translate( -(velocity) * gameTime, 0);

		//down
		if (downLimit && down && (window->KeyDown(VK_DOWN) || window->KeyDown('S')))
			Translate(0, velocity * gameTime);
	}
	
	/*
	//espaço
	if (spcCtrl && window->KeyDown(VK_SPACE)) {
		score++;
		spcCtrl = false;
	}
	else if (window->KeyUp(VK_SPACE))
		spcCtrl = true;
	*/

	//soltar bomba
	if (!bombPlanted && bombsLeft > 0 && shootCtrl && (window->KeyDown('Z') || window->KeyDown('K')) ) {

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

	top = true;
	down = true;
	left = true;
	right = true;
	bombPlanted = false;

	anim->Select(state);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------
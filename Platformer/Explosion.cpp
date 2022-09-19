/**********************************************************************************
// Background (Código Fonte)
//
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plano de fundo do jogo
//
**********************************************************************************/

#include "Explosion.h"
#include "BombZombie.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(float posX, float posY, uint direction, uint size)//construtor das explosões "filhas"
{
    tileSet = new TileSet("Resources/explosion.png", 40, 40, 7, 7);
    anim = new Animation(tileSet, 0.05f, false);

    uint boom[7] = { 0,1,2,3,4,5,6 };

    anim->Add(0, boom, 7);
    
    BBox(new Rect(20, -20, 20, 20));
    
    type = EXPLOSION;
	this->direction = direction;
	this->posX = posX;
	this->posY = posY;
	this->size = size;
	extend = false;
	isOrigin = false;
	started = true;
    
    MoveTo(posX, posY, Layer::FRONT);
}

Explosion::Explosion(float posX, float posY, uint size)//construtor da explosão "pai"
{
	tileSet = new TileSet("Resources/explosion.png", 40, 40, 7, 7);
	anim = new Animation(tileSet, 0.05f, false);

	uint boom[7] = { 0,1,2,3,4,5,6 };

	anim->Add(0, boom, 7);

	BBox(new Rect(20, -20, 20, 20));

	type = EXPLOSION;
	this->direction = TOP; //inicializa apenas para evitar warning
	this->posX = posX;
	this->posY = posY;
	this->size = size;
	extend = false;
	isOrigin = true;
	started = true;

	MoveTo(posX, posY, Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Explosion::~Explosion()
{
    delete anim;
    delete tileSet;
}

// -------------------------------------------------------------------------------

void Explosion::OnCollision(Object* obj) {
	if (obj->Type() == PIVOT || obj->Type() == OBSTACLE) {
		
		if (x == obj->X() && y == obj->Y()) {
			
			BombZombie::scene->Delete(this, MOVING);
		}
		else {
			extend = true;
		}

	}
	else {
		extend = true;
	}
}

// -------------------------------------------------------------------------------

void Explosion::Update()
{
	if (x < 30.0f)
		BombZombie::scene->Delete(this, MOVING);
	if (y < 130.0f)
		BombZombie::scene->Delete(this, MOVING);
	if (x + 20.0f > 530.0f)
		BombZombie::scene->Delete(this, MOVING);
	if (y + 20.0f > 630.0f)
		BombZombie::scene->Delete(this, MOVING);

	if (anim->Frame() >= 4)//a partir do frame 4 já não causa mais dano
		type = 0;

	if (anim->Frame() == 6)
		BombZombie::scene->Delete(this, MOVING);
	
	if (extend && started && size > 0) {
		if (isOrigin) {
			eT = new Explosion(posX, posY - 40.0f, TOP, size - 1);
			BombZombie::scene->Add(eT, MOVING);

			eL = new Explosion(posX - 40.0f, posY, LEFT, size - 1);
			BombZombie::scene->Add(eL, MOVING);

			eR = new Explosion(posX + 40.0f, posY, RIGHT, size - 1);
			BombZombie::scene->Add(eR, MOVING);

			eD = new Explosion(posX, posY + 40.0f, DOWN, size - 1);
			BombZombie::scene->Add(eD, MOVING);
		}
		else {
			if (direction == TOP) {
				eT = new Explosion(posX, posY - 40.0f, direction, size - 1);
				BombZombie::scene->Add(eT, MOVING);
			}
			else if (direction == LEFT) {
				eL = new Explosion(posX - 40.0f, posY, direction, size - 1);
				BombZombie::scene->Add(eL, MOVING);
			}
			else if (direction == RIGHT) {
				eR = new Explosion(posX + 40.0f, posY, direction, size - 1);
				BombZombie::scene->Add(eR, MOVING);
			}
			else if (direction == DOWN) {
				eD = new Explosion(posX, posY + 40.0f, direction, size - 1);
				BombZombie::scene->Add(eD, MOVING);
			}
		}
		started = false;
	}

	anim->NextFrame();
}

// -------------------------------------------------------------------------------

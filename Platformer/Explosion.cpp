/**********************************************************************************
// Background (C�digo Fonte)
//
// Cria��o:     21 Abr 2012
// Atualiza��o: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Plano de fundo do jogo
//
**********************************************************************************/

#include "Explosion.h"
#include "BombZombie.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(float posX, float posY, uint direction, uint size)//construtor das explos�es "filhas"
{
    tileSet = new TileSet("Resources/explosion.png", 36, 40, 7, 7);
    anim = new Animation(tileSet, 0.06f, false);

    uint boom[7] = { 0,1,2,3,4,5,6 };

    anim->Add(0, boom, 7);
    
    BBox(new Rect(18, -20, 18, 20));
    
    type = EXPLOSION;
	this->direction = direction;
	this->posX = posX;
	this->posY = posY;
	this->size = size;
	extend = true;
	isOrigin = false;
	started = true;
    
    MoveTo(posX, posY, Layer::FRONT);
}

Explosion::Explosion(float posX, float posY, uint size)//construtor da explos�o "pai"
{
	tileSet = new TileSet("Resources/explosion.png", 36, 40, 7, 7);
	anim = new Animation(tileSet, 0.06f, false);

	uint boom[7] = { 0,1,2,3,4,5,6 };

	anim->Add(0, boom, 7);

	BBox(new Rect(18, -20, 18, 20));

	type = EXPLOSION;
	this->direction = TOP; //inicializa apenas para evitar warning
	this->posX = posX;
	this->posY = posY;
	this->size = size;
	extend = true;
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
		/* Calcula a diferen�a de distancia do centro da 
		explos�o e do grid (� utilizado o m�dulo do valor!!!)*/

		float xDiff = x - obj->X() > 0 ? x - obj->X() : -(x - obj->X());
		float yDiff = y - obj->Y() > 0 ? y - obj->Y() : -(y - obj->Y());

		if (xDiff <= 20.0f && yDiff <= 20.0f) {
			extend = false;
		}
	}
}

// -------------------------------------------------------------------------------

void Explosion::Update()
{
	if (anim->Frame() >= 6)
		BombZombie::scene->Delete(this, MOVING);

	if (extend && started && size > 0) {
		if (isOrigin) {
			Explosion* eT = new Explosion(posX, posY - 40.0f, TOP, size - 1);
			BombZombie::scene->Add(eT, MOVING);

			Explosion* eL = new Explosion(posX - 40.0f, posY, LEFT, size - 1);
			BombZombie::scene->Add(eL, MOVING);

			Explosion* eR = new Explosion(posX + 40.0f, posY, RIGHT, size - 1);
			BombZombie::scene->Add(eR, MOVING);

			Explosion* eD = new Explosion(posX, posY + 40.0f, DOWN, size - 1);
			BombZombie::scene->Add(eD, MOVING);
		}
		else {
			if (direction == TOP) {
				Explosion* eT = new Explosion(posX, posY - 40.0f, direction, size - 1);
				BombZombie::scene->Add(eT, MOVING);
			}
			else if (direction == LEFT) {
				Explosion* eL = new Explosion(posX - 40.0f, posY, direction, size - 1);
				BombZombie::scene->Add(eL, MOVING);
			}
			else if (direction == RIGHT){
				Explosion* eR = new Explosion(posX + 40.0f, posY, direction, size - 1);
				BombZombie::scene->Add(eR, MOVING);
			}
			else if (direction == DOWN){
				Explosion* eD = new Explosion(posX, posY + 40.0f, direction, size - 1);
				BombZombie::scene->Add(eD, MOVING);
			}
		}
	}
	started = false;
	anim->NextFrame();
}

// -------------------------------------------------------------------------------

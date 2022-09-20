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

#include "Bomb.h"
#include "BombZombie.h"

// ---------------------------------------------------------------------------------

Bomb::Bomb(uint size, float posX, float posY)//construtor da dinamite
{
    
    sprite1 = new Sprite("Resources/bomb1.png");
    sprite2 = new Sprite("Resources/bomb2.png");
    sprite3 = new Sprite("Resources/bomb3.png");
	BombZombie::player->bombsLeft--;

    BBox(new Rect(-20, -20, 20, 20));
    MoveTo(posX, posY,Layer::MIDDLE);
    type = BOMB;
    this->size = size;
    this->posX = posX;
    this->posY = posY;
	exploded = false;

    timer.Start();
   
}

// ---------------------------------------------------------------------------------

Bomb::~Bomb()
{
    delete sprite1;
    delete sprite2;
    delete sprite3;

}

// -------------------------------------------------------------------------------

void Bomb::OnCollision(Object* obj) {
    
    if (obj->Type() == EXPLOSION) {
		float xDiff = x - obj->X();
		float yDiff = y - obj->Y();

		if (xDiff < 0)
			xDiff = -xDiff;
		if (yDiff < 0)
			yDiff = -yDiff;

		if ((xDiff < 20.0f && yDiff < 40.0f) || (xDiff < 40.0f && yDiff < 20.0f)) {
			Explosion* exp = new Explosion(posX, posY, size);
			exploded = true;
			BombZombie::scene->Add(exp, MOVING);
			BombZombie::player->bombsLeft++;
			BombZombie::scene->Delete(this, MOVING);
		}
    }
}

void Bomb::Update() {

	if (this->timer.Elapsed(3.0f) && !exploded) {
		//OBS.:ajusta a posição X, pois a explosão tem 36px de largura, enquanto que a bomba tem 40px
		Explosion* exp = new Explosion(posX, posY, size);
		BombZombie::scene->Add(exp, MOVING);
		exploded = true;
	}
	if (timer.Elapsed() > 4.0f) {
		BombZombie::player->bombsLeft++;
		BombZombie::scene->Delete(this, MOVING);
	}
}
// -------------------------------------------------------------------------------
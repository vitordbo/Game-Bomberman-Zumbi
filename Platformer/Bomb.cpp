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
#include "Explosion.h"
#include "BombZombie.h"

// ---------------------------------------------------------------------------------

Bomb::Bomb(uint size, float posX, float posY)//construtor da dinamite
{
    
    sprite1 = new Sprite("Resources/bomb1.png");
    sprite2 = new Sprite("Resources/bomb2.png");
    sprite3 = new Sprite("Resources/bomb3.png");

    BBox(new Rect(-20, -20, 20, 20));
    MoveTo(posX, posY);
    type = BOMB;
    this->size = size;
    this->posX = posX;
    this->posY = posY;
	//countdown = 3;
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

//void Bomb::OnCollision(Object* obj) {
//    
//}

void Bomb::Update() {

	if (this->timer.Elapsed(3.0f)) {
		//OBS.:ajusta a posição X, pois a explosão tem 36px de largura, enquanto que a bomba tem 40px
		Explosion* e = new Explosion(posX + 2.0f, posY, size);
		BombZombie::scene->Add(e, MOVING);
	}
	if (timer.Elapsed() > 4.0f) {
		BombZombie::scene->Delete(this, MOVING);
	}
}
// -------------------------------------------------------------------------------
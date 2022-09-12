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

#include "Bullet.h"
#include "BombZombie.h"

// ---------------------------------------------------------------------------------

Bullet::Bullet(uint direction, float posX, float posY)
{
    sprite = new Sprite("Resources/bullet.png");
    MoveTo(posX, posY);
    
    velX = 0.0f;
    velY = 0.0f;

    switch (direction)
    {
    case UP:
        velY = -200.0f;
        break;
    case RIGHT:
        velX = 200.0f;
        break;
    case LEFT:
        velX = -200.0f;
        break;
    case DOWN:
        velY = 200.0f;
        break;
    }

    type = BULLET;
}

// ---------------------------------------------------------------------------------

Bullet::~Bullet()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Bullet::OnCollision(Object* obj) 
{
	Bullet::~Bullet();
	//BombZombie::scene->Remove();
}

// -------------------------------------------------------------------------------

void Bullet::Update()
{
    Translate(velX * gameTime, velY * gameTime);
	if (x < 0 || x > window->Width() || y < 0 || y > window->Height())
		Bullet::~Bullet();
		//BombZombie::scene->Remove();
}

// -------------------------------------------------------------------------------

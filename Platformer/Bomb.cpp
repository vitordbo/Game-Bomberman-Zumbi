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

#include "Bomb.h"
#include "Explosion.h"
#include "BombZombie.h"

// ---------------------------------------------------------------------------------

Bomb::Bomb(uint size, float posX, float posY)//construtor da dinamite
{
    
    sprite = new Sprite("Resources/bomb1.png");
    MoveTo(posX, posY);
    type = BOMB;
    countdown = 3;
    this->size = size;
    this->posX = posX;
    this->posY = posY;
    timer.Start();
   
}

// ---------------------------------------------------------------------------------

Bomb::~Bomb()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Bomb::Update()
{
    if (timer.Elapsed(1.f))
        sprite = new Sprite("Resources/bomb2.png");

    if (timer.Elapsed(2.f))
        sprite = new Sprite("Resources/bomb3.png");


    if (timer.Elapsed(3.0f)) {
        //OBS.:ajusta a posi��o X, pois a explos�o tem 36px de largura, enquanto que a bomba tem 40px

        //explos�es no topo
        for (int i = 0; i < size; i++) {
            Explosion* e = new Explosion(posX + 2.0f, posY - (40.0f * i), posX + 2.0f, posY);
            BombZombie::scene->Add(e, MOVING);
        }

        //explos�es na esquerda
        for (int i = 0; i < size; i++) {
            Explosion* e = new Explosion(posX + 2.0f - (36.0f * i), posY, posX + 2.0f, posY);
            BombZombie::scene->Add(e, MOVING);
        }

        //explos�es em baixo
        for (int i = 0; i < size; i++) {
            Explosion* e = new Explosion(posX + 2.0f, posY + (40.0f * i), posX + 2.0f, posY);
            BombZombie::scene->Add(e, MOVING);
        }

        //explos�es na direita
        for (int i = 0; i < size; i++) {
            Explosion* e = new Explosion(posX + 2.0f + (36.0f * i), posY, posX + 2.0f, posY);
            BombZombie::scene->Add(e, MOVING);
        }
        BombZombie::scene->Delete(this, STATIC);
    }
}

// -------------------------------------------------------------------------------

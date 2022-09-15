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

Explosion::Explosion(float posX, float posY, float posXInit, float posYInit)//construtor da dinamite
{
    tileSet = new TileSet("Resources/explosion.png", 36, 40, 7, 7);
    anim = new Animation(tileSet, 0.06f, false);

    uint boom[7] = { 0,1,2,3,4,5,6 };

    anim->Add(0, boom, 7);
    
    BBox(new Rect(18, -20, 18, 20));
    
    type = EXPLOSION;
    this->posXInit = posXInit;
    this->posYInit = posYInit;
    MoveTo(posX, posY);
}

// ---------------------------------------------------------------------------------

Explosion::~Explosion()
{
    delete anim;
    delete tileSet;
}

// -------------------------------------------------------------------------------

void Explosion::Update()
{
    anim->Select(0);
    anim->NextFrame();
    
    if(anim->Frame() >= 6)
        BombZombie::scene->Delete(this, MOVING);
}

// -------------------------------------------------------------------------------

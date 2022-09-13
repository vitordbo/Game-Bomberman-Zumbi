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

#include "Heart.h"

// ---------------------------------------------------------------------------------

Heart::Heart(Player* player, float posX)
{
    sprite = new Sprite("Resources/heart.png");
    MoveTo(posX, 60.0f);
    this->player = player;
}

Heart::~Heart()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Heart::Update()
{
    
}

// -------------------------------------------------------------------------------

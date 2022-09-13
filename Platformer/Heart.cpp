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

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

#include "Score.h"

// ---------------------------------------------------------------------------------

Score::Score(Player* player)
{
    font = new Font("Resources/consolas12.png");
    this->player = player;
}

Score::~Score()
{
    delete font;
}

// -------------------------------------------------------------------------------


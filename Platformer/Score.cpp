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

Score::Score(Player* player, float posX, float posY)
{
    this->posX = posX;
    this->posY = posY;
    font = new Font("Resources/font.png");
    this->player = player;
}

Score::~Score()
{
    delete font;
}

// -------------------------------------------------------------------------------


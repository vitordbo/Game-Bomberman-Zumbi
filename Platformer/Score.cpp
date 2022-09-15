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


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

#include "Background.h"

// ---------------------------------------------------------------------------------

Background::Background()
{
    // carrega imagens
    sprite = new Sprite("Resources/mapa-01.png");
    MoveTo(window->CenterX(), window->CenterY(), Layer::BACK);
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Background::Update()
{

}

// -------------------------------------------------------------------------------

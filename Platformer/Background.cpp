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

Background::Background(uint mapa)
{
	if (mapa == CAMPO_DIA)
		sprite = new Sprite("Resources/mapa-campo.png");
	else if (mapa == CEMITERIO_NOITE)
		sprite = new Sprite("Resources/mapa-cemiterio-noite.png");
	else
		sprite = new Sprite("Resources/mapa-fabrica.png");

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

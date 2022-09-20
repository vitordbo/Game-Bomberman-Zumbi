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

#include "Fence.h"

// ---------------------------------------------------------------------------------

Fence::Fence(uint mapa)
{
	if(mapa == CAMPO)
		sprite = new Sprite("Resources/cerca-campo.png");
	else if(mapa == CEMITERIO)
		sprite = new Sprite("Resources/cerca-cemiterio.png");
	else
		sprite = new Sprite("Resources/cerca-fabrica.png");

	MoveTo(window->CenterX(), window->CenterY(), Layer::UPPER);
}

// ---------------------------------------------------------------------------------

Fence::~Fence()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

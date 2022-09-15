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

#include "Fence.h"

// ---------------------------------------------------------------------------------

Fence::Fence()
{
    // carrega imagens
    sprite = new Sprite("Resources/fence-mapa-02.png");
    MoveTo(window->CenterX(), window->CenterY(), Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Fence::~Fence()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

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

Heart::Heart(Player* player)
{
    // carrega imagens
    if (player->hp == 5) {
        sprite = new Sprite("Resources/heart5.png");
        MoveTo(180.0f, 60.0f);
    }
    else {
        sprite = new Sprite("Resources/heart3.png");
        MoveTo(120.0f, 60.0f);
    }
    this->player = player;
}

// ---------------------------------------------------------------------------------

Heart::~Heart()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Heart::Update()
{
    if(player->hp == 5){
        sprite = new Sprite("Resources/heart5.png");
        MoveTo(180.0f, 60.0f);
    }
    else if (player->hp == 4) {
        sprite = new Sprite("Resources/heart4.png");
        MoveTo(150.0f, 60.0f);
    }
    else if(player->hp == 3) {
        sprite = new Sprite("Resources/heart3.png");
        MoveTo(120.0f, 60.0f);
    }
    else if (player->hp == 2) {
        sprite = new Sprite("Resources/heart2.png");
        MoveTo(90.0f, 60.0f);
    }
    else if (player->hp == 1) {
        sprite = new Sprite("Resources/heart.png");
        MoveTo(60.0f, 60.0f);
    }
    else {
        sprite = new Sprite("Resources/heartZERO.png");
        MoveTo(60.0f, 60.0f);
    }
}

// -------------------------------------------------------------------------------

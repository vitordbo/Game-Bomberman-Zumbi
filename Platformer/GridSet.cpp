/**********************************************************************************
// Platform (C�digo Fonte)
// 
// Cria��o:     21 Abr 2012
// Atualiza��o: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Plataformas do jogo
//
**********************************************************************************/

#include "GridSet.h"

// ---------------------------------------------------------------------------------

GridSet::GridSet(float posX, float posY, uint i, uint j, uint index, uint type)
{ 
    if (type == OBSTACLE) {
        sprite = new Sprite("Resources/trash.png");
    }
    this->i = i;
    this->j = j;
    this->type = type;
    BBox(new Rect(-20, -20, 20, 20));
    MoveTo(posX, posY);
}

// ---------------------------------------------------------------------------------

GridSet::~GridSet()
{
    delete sprite;
}

/**********************************************************************************
// Platform (Código Fonte)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#include "GridSet.h"

// ---------------------------------------------------------------------------------

GridSet::GridSet(float posX, float posY, uint i, uint j, uint index, uint type)
{ 
	sprite = new Sprite("Resources/trash.png");
    this->i = i;
    this->j = j;
    this->type = type;
	this->index = index;
    BBox(new Rect(-20, -20, 20, 20));
    MoveTo(posX, posY);
}

// ---------------------------------------------------------------------------------

void GridSet::OnCollision(Object* obj) {

	if (type == OBSTACLE) {
		if (obj->Type() == EXPLOSION) {
			type = GRID;
		}
	}
}

// ---------------------------------------------------------------------------------

GridSet::~GridSet()
{
    delete sprite;
}

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
#include "BombZombie.h"

// ---------------------------------------------------------------------------------

GridSet::GridSet(float posX, float posY, uint i, uint j, uint index, uint type)
{ 
    tileSet = new TileSet("Resources/box.png", 40, 40, 8, 8);
    anim = new Animation(tileSet, 0.05f, false);
    
    uint normal[1] = { 0 };
    uint exploded[7] = { 1,2,3,4,5,6,7 };
    
    anim->Add(0, normal, 1);
    anim->Add(1, exploded, 7);

    this->i = i;
    this->j = j;
    this->type = type;
	this->index = index;
    destroyed = false;

    BBox(new Rect(-20, -20, 20, 20));
    MoveTo(posX, posY);
}

// ---------------------------------------------------------------------------------

void GridSet::OnCollision(Object* obj) {

    float xDiff = x - obj->X();
    float yDiff = y - obj->Y();

    if (xDiff < 0)
        xDiff = -xDiff;
    if (yDiff < 0)
        yDiff = -yDiff;

	if (type == OBSTACLE) 
		if (obj->Type() == EXPLOSION) 
            if (yDiff < 38.0f && xDiff < 38.0f)
                destroyed = true;
}

// ---------------------------------------------------------------------------------

GridSet::~GridSet()
{
    delete anim;
    delete tileSet;
}

// ---------------------------------------------------------------------------------

void GridSet::Update() {
    if (anim->Frame() == 7)
        this->type = GRID;

    if (!destroyed)
        anim->Select(0);
    else {
        anim->Select(1);
    }
    anim->NextFrame();
}
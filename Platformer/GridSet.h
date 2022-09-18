/**********************************************************************************
// Platform (Arquivo de Cabe�alho)
// 
// Cria��o:     21 Abr 2012
// Atualiza��o: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Plataformas do jogo
//
**********************************************************************************/

#ifndef _BOMBZOMBIE_GRIDSET_H_
#define _BOMBZOMBIE_GRIDSET_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "TileSet.h"                     // background � composto por sprites
#include "Animation.h" 

class GridSet : public Object
{
private:
    TileSet* tileSet = nullptr;            
    Animation* anim = nullptr;             
public:
    uint i;
    uint j;
    uint index;

    bool destroyed;
    
    GridSet(float posX, float posY, uint i, uint j, uint index, uint type);
    ~GridSet();

    void Update();                      // atualiza��o do objeto
	void OnCollision(Object* obj);
    void Draw();                        // desenho do objeto
}; 

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void GridSet::Draw(){
    if (type == OBSTACLE)
        anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif
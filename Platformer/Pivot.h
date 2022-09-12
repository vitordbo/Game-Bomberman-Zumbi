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

#ifndef _BOMBZOMBIE_PIVOT_H_
#define _BOMBZOMBIE_PIVOT_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background � composto por sprites

// ---------------------------------------------------------------------------------

enum PLATTYPES { SMALL, MEDIUM, LARGE };

// ---------------------------------------------------------------------------------

class Pivot : public Object
{
private:

public:
    Pivot(float posX, float posY);    
    ~Pivot();

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
}; 

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Pivot::Draw(){}
inline void Pivot::Update(){}

// ---------------------------------------------------------------------------------

#endif
/**********************************************************************************
// Background (Arquivo de Cabe�alho)
//
// Cria��o:     21 Abr 2012
// Atualiza��o: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Plano de fundo do jogo
//
**********************************************************************************/

#ifndef _BOMBZOMBIE_HEART_H_
#define _BOMBZOMBIE_HEART_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background � composto por sprites
#include "Player.h"

// ---------------------------------------------------------------------------------

class Heart : public Object
{
private:
    Sprite* sprite;                         // fundo est�tico   
    Player* player;
public:
    Heart(Player* player);                                // construtor
    ~Heart();                               // destrutor

    void Update();                          // atualiza��o do objeto
    void Draw();                            // desenho do objeto
};


// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Heart::Draw()
{
    sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
#endif
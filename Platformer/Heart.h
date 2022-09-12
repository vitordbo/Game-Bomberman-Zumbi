/**********************************************************************************
// Background (Arquivo de Cabeçalho)
//
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plano de fundo do jogo
//
**********************************************************************************/

#ifndef _BOMBZOMBIE_HEART_H_
#define _BOMBZOMBIE_HEART_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background é composto por sprites
#include "Player.h"

// ---------------------------------------------------------------------------------

class Heart : public Object
{
private:
    Sprite* sprite;                         // fundo estático   
    Player* player;
public:
    Heart(Player* player);                                // construtor
    ~Heart();                               // destrutor

    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
};


// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Heart::Draw()
{
    sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
#endif
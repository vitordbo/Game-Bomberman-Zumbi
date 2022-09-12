/**********************************************************************************
// Player (Arquivo de Cabe�alho)
//
// Cria��o:     20 Abr 2012
// Atualiza��o: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Define uma classe para o jogador
//
**********************************************************************************/

#ifndef _BOMBZOMBIE_ZOMBIE_H_
#define _BOMBZOMBIE_ZOMBIE_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites
#include "Pivot.h"

// ------------------------------------------------------------------------------

enum Movimento {
    DWN_MOVE, DWN_IDLE,
    LFT_MOVE, LFT_IDLE,
    TP_MOVE, TP_IDLE,
    RGT_MOVE, RGT_IDLE
}; // tipo de movimento

// ---------------------------------------------------------------------------------

class Zombie : public Object
{
private:
    TileSet* tileset = nullptr;            // folha de sprites do personagem
    Animation* anim = nullptr;             // anima��o do personagem

public:
    int hp;                                 //pontos de vida
    uint state;
    Zombie();                           // construtor
    ~Zombie();                          // destrutor

    void OnCollision(Object* obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Zombie::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif
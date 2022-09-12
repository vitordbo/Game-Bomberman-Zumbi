/**********************************************************************************
// Player (Arquivo de Cabeçalho)
//
// Criação:     20 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para o jogador
//
**********************************************************************************/

#ifndef _BOMBZOMBIE_ZOMBIE_H_
#define _BOMBZOMBIE_ZOMBIE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites
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
    Animation* anim = nullptr;             // animação do personagem

public:
    int hp;                                 //pontos de vida
    uint state;
    Zombie();                           // construtor
    ~Zombie();                          // destrutor

    void OnCollision(Object* obj);     // resolução da colisão
    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Zombie::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------

#endif
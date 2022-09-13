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

#ifndef _BOMBZOMBIE_PLAYER_H_
#define _BOMBZOMBIE_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites
#include "Pivot.h"

// ------------------------------------------------------------------------------

enum Type { DOWN_MOVE, DOWN_IDLE, 
            LEFT_MOVE, LEFT_IDLE, 
            TOP_MOVE, TOP_IDLE, 
            RIGHT_MOVE, RIGHT_IDLE}; // tipo de movimento

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet * tileset = nullptr;            // folha de sprites do personagem
    Animation * anim = nullptr;             // animação do personagem
    bool spcCtrl;                           // controle do pressionamento da barra de espaço
	bool shootCtrl;							//controle dos botões de disparo
   

    
    

public:
    uint hp;                                 //pontos de vida
    uint bombSize;
    uint state;
    Player();                           // construtor
    ~Player();                          // destrutor

    void OnCollision(Object * obj);     // resolução da colisão
    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Player::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif
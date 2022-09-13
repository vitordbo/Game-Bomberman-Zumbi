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

#ifndef _BOMBZOMBIE_PLAYER_H_
#define _BOMBZOMBIE_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites
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
    Animation * anim = nullptr;             // anima��o do personagem
    bool spcCtrl;                           // controle do pressionamento da barra de espa�o
	bool shootCtrl;							//controle dos bot�es de disparo
   

    
    

public:
    uint hp;                                 //pontos de vida
    uint bombSize;
    uint state;
    Player();                           // construtor
    ~Player();                          // destrutor

    void OnCollision(Object * obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Player::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif
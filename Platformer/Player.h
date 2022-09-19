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
#include "GridSet.h"
#include "Bomb.h"
#include "Timer.h"

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
	Timer t;								//temporizador interno
	GridSet ** gridSet = nullptr;

    bool spcCtrl;                           // controle do pressionamento da barra de espa�o
	bool shootCtrl;							//controle dos bot�es de disparo
	bool bombPlanted;						//boolean que indica se j� existe uma bomba neste grid
	bool immune;							//boolean para controlar o hp quando sofrer dano 
	bool blinkEffect = false;				//boolena para controlar efeito visual durante imunidade

	bool leftLimit;
	bool rightLimit;
	bool topLimit;
	bool downLimit;

	bool top;
	bool left;
	bool right;
	bool down;
  
public:
    uint gridI; //valor do label i do grid em que player est�
    uint gridJ; //valor do label j do grid em que player est�
    uint gridIndex;

	uint bombsMax;					 //qnt maxima de bomba permitida
	uint bombsLeft;				     //bombas restantes para soltar
    uint hp;                         //pontos de vida
    uint score;
    uint bombSize;
    uint state;

    Player(GridSet ** gridSet);         // construtor
    ~Player();                          // destrutor

    void OnCollision(Object * obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
	void Immune();						//m�todo que controla o tempo de imunidade
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Player::Draw()
{
	if (immune) {
		if (blinkEffect) {
			anim->Draw(x, y, z);
			blinkEffect = false;
		}
		else {
			blinkEffect = true;
		}
	}
	else {
		anim->Draw(x, y, z);
	}
}
//TODO
inline void Player::Immune() {
	
	if (t.Elapsed() > 3.0f) {
		immune = false;
		t.Reset();
	}
}

// ---------------------------------------------------------------------------------

#endif
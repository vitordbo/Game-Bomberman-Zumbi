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
#include "Player.h"

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
	TileSet* tileset = nullptr;					// folha de sprites do personagem
	Animation* anim = nullptr;					// anima��o do personagem
	GridSet** gridSet = nullptr;
	Player* player;

public:
	uint gridI;									//valor do label i do grid em que player est�
	uint gridJ;									//valor do label j do grid em que player est�
	uint gridIndex;

	bool right;
	bool left;
	bool top;
	bool down;

	bool rightTemp;
	bool leftTemp;
	bool topTemp;
	bool downTemp;

	int temp;

	int hp;										//pontos de vida
	uint state;
	Zombie(Player* player, GridSet** gridSet, uint i, uint j);  // construtor
	~Zombie();									// destrutor

	void OnCollision(Object* obj);				// resolu��o da colis�o
	void Update();								// atualiza��o do objeto
	void Draw();								// desenho do objeto

	float distanceX();
	float distanceY();
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Zombie::Draw()
{
	anim->Draw(x, y, z);
}

inline float Zombie::distanceX()
{
	return x - player->X();
}

inline float Zombie::distanceY()
{
	return y - player->Y();
}

// ---------------------------------------------------------------------------------

#endif
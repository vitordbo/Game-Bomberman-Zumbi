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
	Animation* anim = nullptr;					// animação do personagem
	GridSet** gridSet = nullptr;
	Player* player;

public:
	uint gridI;									//valor do label i do grid em que player está
	uint gridJ;									//valor do label j do grid em que player está
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

	void OnCollision(Object* obj);				// resolução da colisão
	void Update();								// atualização do objeto
	void Draw();								// desenho do objeto

	float distanceX();
	float distanceY();
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

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
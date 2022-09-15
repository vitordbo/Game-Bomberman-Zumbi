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

#ifndef _BOMBZOMBIE_EXPLOSION_H_
#define _BOMBZOMBIE_EXPLOSION_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background é composto por sprites
#include "Player.h"
#include "Animation.h"
#include "TileSet.h"

enum ExpDirect {TOP, LEFT, RIGHT, DOWN};

class Explosion : public Object
{
private: 
    Animation* anim;
    TileSet* tileSet;
    float posX;
    float posY;
   
public:
	uint direction;
	bool extend;											//booleando que indica se a bomba "encostou" em um pivot ou obstacle
	bool isOrigin;
	bool started;											//boolean de controle para instanciar as explosões filhas UMA vez apenas!!!
	uint size;												//tamanho da explosão 
    Explosion* eT = nullptr;
    Explosion* eD = nullptr;
    Explosion* eL = nullptr;
    Explosion* eR = nullptr;

    Explosion(float posX, float posY, uint direction, uint size);
	Explosion(float posX, float posY, uint size);           //construtor da explosão origem
    ~Explosion();                                           // destrutor

    void Update();                                          // atualização do objeto
	void OnCollision(Object* obj);
    void Draw();                                            // desenho do objeto
};


// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Explosion::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
#endif
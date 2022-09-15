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

#ifndef _BOMBZOMBIE_EXPLOSION_H_
#define _BOMBZOMBIE_EXPLOSION_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background � composto por sprites
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
	bool started;											//boolean de controle para instanciar as explos�es filhas UMA vez apenas!!!
	uint size;												//tamanho da explos�o 
    Explosion* eT = nullptr;
    Explosion* eD = nullptr;
    Explosion* eL = nullptr;
    Explosion* eR = nullptr;

    Explosion(float posX, float posY, uint direction, uint size);
	Explosion(float posX, float posY, uint size);           //construtor da explos�o origem
    ~Explosion();                                           // destrutor

    void Update();                                          // atualiza��o do objeto
	void OnCollision(Object* obj);
    void Draw();                                            // desenho do objeto
};


// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Explosion::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
#endif
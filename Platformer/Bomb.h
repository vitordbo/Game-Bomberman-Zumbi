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

#ifndef _BOMBZOMBIE_BOMB_H_
#define _BOMBZOMBIE_BOMB_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background � composto por sprites
#include "Player.h"
#include "Timer.h"
#include "Animation.h"
#include "TileSet.h"

class Bomb : public Object
{
private:
    Sprite* sprite1;
    Sprite* sprite2;                                          // fundo est�tico  
    Sprite* sprite3;                                          // fundo est�tico  

    Timer timer;
    uint size;
	//uint countdown; //inteiro usado para evitar m�ltiplas instancia��es de uma mesma bomba
    float posX;
    float posY;
public:
    Bomb(uint size, float posX, float posY);                 // construtor
 
    ~Bomb();                                                  // destrutor

    //void OnCollision(Object* obj);                          // resolu��o da colis�o
    void Update();                                          // atualiza��o do objeto
    void Draw();                                            // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Bomb::Draw()
{
    if (this->timer.Elapsed() < 1.0f) {
        sprite1->Draw(x, y, z);
    }
    else if (this->timer.Elapsed() < 2.0f) {
        sprite2->Draw(x, y, z);
    }
    else if (this->timer.Elapsed() < 3.0f) {
        sprite3->Draw(x, y, z);
    }
}

// ---------------------------------------------------------------------------------
#endif
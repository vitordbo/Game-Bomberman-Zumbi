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

class Explosion : public Object
{
private: 
    Animation* anim;
    TileSet* tileSet;
    float posXInit;
    float posYInit;
   
public:
    Explosion(float posX, float posY, float posXInit, float posYInit);
    ~Explosion();                                                  // destrutor

    void Update();                                          // atualiza��o do objeto
    void OnCollision(Object* obj);                           // resolu��o da colis�o
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
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

    void Update();                                          // atualização do objeto
    void OnCollision(Object* obj);                           // resolução da colisão
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
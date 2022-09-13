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
    Sprite* sprite;                                          // fundo est�tico  
    Timer timer;
    uint countdown;
    uint size;
    float posX;
    float posY;
public:
    Bomb(uint size, float posX, float posY);                 // construtor
 
    ~Bomb();                                                  // destrutor

    void Update();                                          // atualiza��o do objeto
    void Draw();                                            // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Bomb::Draw()
{
    sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
#endif
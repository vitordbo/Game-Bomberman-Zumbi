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

#ifndef _BOMBZOMBIE_BULLET_H_
#define _BOMBZOMBIE_BULLET_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background é composto por sprites
#include "Player.h"

// ---------------------------------------------------------------------------------

enum Direction { UP, DOWN, LEFT, RIGHT };

// ---------------------------------------------------------------------------------

class Bullet : public Object
{
private:
    Sprite* sprite;                                          // fundo estático   
    float velX, velY;
public:
    Bullet(uint direction, float posX, float posY);                  // construtor
    ~Bullet();                                                  // destrutor

    void Update();                                          // atualização do objeto
    void OnCollision(Object* obj);                           // resolução da colisão
    void Draw();                                            // desenho do objeto
};


// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Bullet::Draw()
{
    sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
#endif
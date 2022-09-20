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

#ifndef _BOMBZOMBIE_BACKGROUND_H_
#define _BOMBZOMBIE_BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background é composto por sprites

// ---------------------------------------------------------------------------------
enum MapaBG { CAMPO_DIA, CEMITERIO_NOITE, FABRICA_DIA };
// ---------------------------------------------------------------------------------

class Background : public Object
{
private: 
    Sprite * sprite;                       // fundo estático   
public:
    Background(uint mapa);                       // construtor
    ~Background();                      // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
}; 


// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Background::Draw()
{
    sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
#endif
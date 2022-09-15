/**********************************************************************************
// Platformer (Arquivo de Cabe�alho)
//
// Cria��o:     05 Out 2011
// Atualiza��o: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Exemplo de jogo estilo platforma
//
**********************************************************************************/

#ifndef _BOMBZOMBIE_H_
#define _BOMBZOMBIE_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Scene.h"
#include "GridSet.h"
#include "Background.h"
#include "Player.h"
#include "Heart.h"
#include "Zombie.h"
#include "Fence.h"

// ------------------------------------------------------------------------------

class BombZombie : public Game
{
private:
    Player * player = nullptr;      // jogador
    GridSet* gridSet = nullptr;     //malha de frames do mapa
    Background * backg = nullptr;   // pano de fundo
    Heart* heart = nullptr;
    Fence* fence = nullptr;
    Zombie* zombie = nullptr;

public:
    static Scene * scene;           // gerenciador de cena

    Heart* h1;
    Heart* h2;
    Heart* h3;

    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif
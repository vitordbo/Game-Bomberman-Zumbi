/**********************************************************************************
// Platformer (Arquivo de Cabeçalho)
//
// Criação:     05 Out 2011
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de jogo estilo platforma
//
**********************************************************************************/

#ifndef _BOMBZOMBIE_H_
#define _BOMBZOMBIE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Scene.h"
#include "GridSet.h"
#include "Background.h"
#include "Player.h"
#include "Heart.h"
#include "Zombie.h"
#include "Fence.h"
#include "Score.h"
// ------------------------------------------------------------------------------

class BombZombie : public Game
{
private:
    Player * player = nullptr;              // jogador
    GridSet ** gridSet = nullptr;           //matriz de frames do mapa
    Background * backg = nullptr;           // pano de fundo
  
    Heart* heart = nullptr;
    Fence* fence = nullptr;
    Zombie* zombie = nullptr;

public:
    static Scene * scene;           // gerenciador de cena

    Heart* h1;
    Heart* h2;
    Heart* h3;
    Score* score;

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif
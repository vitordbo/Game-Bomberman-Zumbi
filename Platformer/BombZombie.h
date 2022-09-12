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
#include "Pivot.h"
#include "Background.h"
#include "Player.h"
#include "Heart.h"
#include "Zombie.h"

// ------------------------------------------------------------------------------

class BombZombie : public Game
{
private:
    Player * player = nullptr;      // jogador
    Pivot* pivot = nullptr;
    Background * backg = nullptr;   // pano de fundo
    Heart* heart = nullptr;
    Zombie* zombie = nullptr;

public:
    static Scene * scene;           // gerenciador de cena

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// ---------------------------------------------------------------------------------

#endif
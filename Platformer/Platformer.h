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

#ifndef _PLATFORMER_H_
#define _PLATFORMER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Scene.h"
#include "Platform.h"
#include "Background.h"
#include "Player.h"

// ------------------------------------------------------------------------------

class Platformer : public Game
{
private:
    Player * player = nullptr;      // jogador
    Platform* platform = nullptr;
    Background * backg = nullptr;   // pano de fundo

public:
    static Scene * scene;           // gerenciador de cena

    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// ---------------------------------------------------------------------------------

#endif
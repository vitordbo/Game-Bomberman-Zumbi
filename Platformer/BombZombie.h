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
#include "Score.h"
#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;
// ------------------------------------------------------------------------------

class BombZombie : public Game
{
private:
    
    GridSet ** gridSet = nullptr;           //matriz de frames do mapa
    Background * backg = nullptr;           // pano de fundo
  
    Heart* heart = nullptr;
    Fence* fence = nullptr;
    Zombie* zombie = nullptr;

    random_device rd;               
    mt19937 mt{ rd() };   

    uniform_real_distribution<float> itemResult{ 0.0f, 10.0f };     // item que surgir� ap�s explos�o (itens v�o de 2 a 4)

    uniform_real_distribution<float> pseudoBoolean{ 0.0f, 1.0f };   // "roda o dado" para verificar se algo vai OU n�o acontecer
    bool doorCreated;                                               //boolean para indicar se j� foi criada uma porta no mapa
    
    uniform_real_distribution<float> qntItens{ 5.0f, 10.0f };       // quantidade de itens permitidos no mapa
    uint itensLeft;                                                 //controla a quantidade restante de itens permitidos

public:
    static Scene * scene;           // gerenciador de cena
	static Player* player;
    Heart* h1;
    Heart* h2;
    Heart* h3;
    Score* score;

    uint zombiesXPos[3]; //vetor que cont�m as posi��es no eixo X dos zumbis
    uint zombiesYPos[3]; //vetor que cont�m as posi��es no eixo Y dos zumbis

    uint zombiesLeft = 3;

    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
	void BombPlanted();				//m�todo para reduzir a quantidade de bombas restantes
	void BombExploded();			//m�todo para liberar uma bomba que explodiu
};

// ---------------------------------------------------------------------------------
inline void BombZombie::BombPlanted() {
	player->bombsLeft -= 1;
}

inline void BombZombie::BombExploded() {
	player->bombsLeft += 1;
}
#endif
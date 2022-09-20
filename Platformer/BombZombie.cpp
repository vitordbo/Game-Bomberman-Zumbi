/**********************************************************************************
// Platformer (Código Fonte)
//
// Criação:     05 Out 2011
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de jogo estilo platforma
//
**********************************************************************************/

#include "Engine.h"
#include "BombZombie.h"
#include "Resources.h"
#include "Home.h"
#include "GameOver.h"
#include "NextLevel.h"
// -----------------------------------------------------------------------------

Scene * BombZombie::scene = nullptr;
Player* BombZombie::player = nullptr;
uint* BombZombie::mapa;

// -----------------------------------------------------------------------------

void BombZombie::Init()
{
    itensLeft = (uint)qntItens(mt);
    doorCreated = false;

    mapa = new uint{ 1 };

    // cria cena do jogo
    scene = new Scene();

    gridSet = new GridSet * [13 * 13];

    uint index = 0;
    //matriz de grades 13x13 (cada grade com 40 x 40px)
    for (int j = 0; j < 13; j++) {
        for (int i = 0; i < 13; i++) {
            
            //obstáculos
            if ((i % 2 == 0 || j % 2 == 0) && (j > 1 || i > 1) && pseudoBoolean(mt) > 0.4f) {
                gridSet[index] = new GridSet(30.0f + (40.0f * (float)i), 130.0f + (40.0f * (float)j), i, j, index, OBSTACLE);
            }
            else {
                //os pivots estão somente em linhas e colunas ímpares
                if (j % 2 != 0) {
                    if (i % 2 != 0) {
                        gridSet[index] = new GridSet(30.0f + (40.0f * (float)i), 130.0f + (40.0f * (float)j), i, j, index, PIVOT);
                    }
                    else {
                        gridSet[index] = new GridSet(30.0f + (40.0f * (float)i), 130.0f + (40.0f * (float)j), i, j, index, GRID);
                    }
                }
                else {
                    gridSet[index] = new GridSet(30.0f + (40.0f * (float)i), 130.0f + (40.0f * (float)j), i, j, index, GRID);
                }
            }

            if (gridSet[index]->Type() == OBSTACLE) {           //só cria objetos pós explosão em obstáculos
                
                /* Se chegou em um certo ponto do vetor, e não 
                tem uma porta ainda, este obstáculo receberá a porta*/
                if (( (uint)pseudoBoolean(mt) == 1 && !doorCreated) || (!doorCreated && index >= 80)) {
                    
                    gridSet[index]->objPosExp = 1;              //esse obstáculo vai ter uma porta quando destruir
                    doorCreated = true;
                }
                //se NÃO criar uma porta, PODERÁ gerar um item caso ainda sobre espaço na variável
                else if(itensLeft > 0) {
                    if ((uint)itemResult(mt) == 2) {
                        gridSet[index]->objPosExp = 2;//medkit
                        itensLeft--;
                    }
                    else if ((uint)itemResult(mt) == 3) {
                        gridSet[index]->objPosExp = 3;//more bomb
                        itensLeft--;
                    }
                    else if ((uint)itemResult(mt) == 4) {
                        gridSet[index]->objPosExp = 4;//extend explosion
                        itensLeft--;
                    }
                }
            }

            //estabelece uma coordenada para criar um zumbi 
            if ((gridSet[index]->Type() == GRID) && index > 70) {
                if (pseudoBoolean(mt) > 0.2f && zombiesLeft > 0) {
                   
                    zombiesXPos[zombiesLeft - 1] = i;
                    zombiesYPos[zombiesLeft - 1] = j;
                    
                    zombiesLeft--;
                }
            }

            scene->Add(gridSet[index], MOVING);
            index++;
        }
    }

    player = new Player(gridSet);
    scene->Add(player, MOVING);

    //criação dos zumbis
    zombie = new Zombie(player,gridSet, zombiesXPos[0], zombiesYPos[0]);
    scene->Add(zombie, MOVING);

    zombie = new Zombie(player, gridSet, zombiesXPos[1], zombiesYPos[1]);
    scene->Add(zombie, MOVING);

    zombie = new Zombie(player, gridSet, zombiesXPos[2], zombiesYPos[2]);
    scene->Add(zombie, MOVING);

    //criação dos corações
    h1 = new Heart(player, 1, 50.0f);
    scene->Add(h1, STATIC);

    h2 = new Heart(player, 2, 110.0f);
    scene->Add(h2, STATIC);

    h3 = new Heart(player, 3, 170.0f);
    scene->Add(h3, STATIC);

    //criação do score
    score = new Score(player);
    scene->Add(score, STATIC);

    // pano de fundo do jogo
    backg = new Background(BombZombie::mapa);
    scene->Add(backg, STATIC);

    //adiciona png de cerca na layer frontal
    fence = new Fence();
    scene->Add(fence, STATIC);
}

// ------------------------------------------------------------------------------

void BombZombie::Update()
{
   
    // Entra na tela menu do jogo
    if (window->KeyDown(VK_ESCAPE))
    {
        Engine::Next<Home>();
    }
    //else if ((zombiesLeft == 0 && (player->gridIndex == DOOR)) || window->KeyDown('P'))
    else if (window->KeyDown('P'))
    {
        mapa++;
        Engine::Next<NextLevel>();
    }
    else if (player->hp <= 0) // Vida menor que zero, player morre
    {
        Engine::Next<GameOver>();
    }
    // atualiza cena do jogo
    else {
        scene->Update();
        scene->CollisionDetection();
    }
} 

// ------------------------------------------------------------------------------

void BombZombie::Draw()
{
    scene->Draw();
    scene->DrawBBox();
} 

// ------------------------------------------------------------------------------

void BombZombie::Finalize()
{
    delete scene;
}


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

// -----------------------------------------------------------------------------

Scene * BombZombie::scene = nullptr;

// -----------------------------------------------------------------------------

void BombZombie::Init()
{
    // cria cena do jogo
    scene = new Scene();

    gridSet = new GridSet * [13 * 13];

    uint index = 0;
    //matriz de grades 13x13 (cada grade com 40 x 40px)
    for (int j = 0; j < 13; j++) {
        for (int i = 0; i < 13; i++) {
            
            //obstáculos
            if (i % 2 == 0 && i != 0) {
                if (j % 2 == 0 && j != 0) {
                    gridSet[index] = new GridSet(30.0f + (40.0f * (float)i), 130.0f + (40.0f * (float)j), i, j, index, OBSTACLE);
                }
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
            scene->Add(gridSet[index], MOVING);
            index++;
        }
    }

    player = new Player(gridSet);
    scene->Add(player, MOVING);

    zombie = new Zombie(player,gridSet);
    scene->Add(zombie, MOVING);

    h1 = new Heart(player, 1, 50.0f);
    scene->Add(h1, STATIC);

    h2 = new Heart(player, 2, 110.0f);
    scene->Add(h2, STATIC);

    h3 = new Heart(player, 3, 170.0f);
    scene->Add(h3, STATIC);

    score = new Score(player);
    scene->Add(score, STATIC);

    // pano de fundo do jogo
    backg = new Background();
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


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura o motor do jogo
    engine->window->Mode(WINDOWED);
    engine->window->Size(540, 640);
    engine->window->Color(150, 200, 230);
    engine->window->Title("BombZombie");
    engine->window->Icon(IDI_ICON);
    //engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    int status = engine->Start(new Home());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------


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

    player = new Player();
    scene->Add(player, MOVING);

    zombie = new Zombie(player);
    scene->Add(zombie, MOVING);

    h1 = new Heart(player, 50.0f);
    scene->Add(h1, STATIC);

    h2 = new Heart(player, 80.0f);
    scene->Add(h2, STATIC);

    h3 = new Heart(player, 110.0f);
    scene->Add(h3, STATIC);

    //primeira linha
    pivot = new Pivot(70.0f, 170.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(150.0f, 170.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(230.0f, 170.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(310.0f, 170.0f);
    scene->Add(pivot, MOVING);

    //segunda linha
    pivot = new Pivot(70.0f, 250.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(150.0f, 250.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(230.0f, 250.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(310.0f, 250.0f);
    scene->Add(pivot, MOVING);

    //terceira linha
    pivot = new Pivot(70.0f, 330.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(150.0f, 330.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(230.0f, 330.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(310.0f, 330.0f);
    scene->Add(pivot, MOVING);

    //quarta linha
    pivot = new Pivot(70.0f, 410.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(150.0f, 410.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(230.0f, 410.0f);
    scene->Add(pivot, MOVING);

    pivot = new Pivot(310.0f, 410.0f);
    scene->Add(pivot, MOVING);

    // pano de fundo do jogo
    backg = new Background();
    scene->Add(backg, STATIC);
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
    engine->window->Size(380, 480);
    engine->window->Color(150, 200, 230);
    engine->window->Title("Platformer");
    engine->window->Icon(IDI_ICON);
    //engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    int status = engine->Start(new Home());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------


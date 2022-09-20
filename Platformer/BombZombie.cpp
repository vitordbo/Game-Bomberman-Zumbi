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
uint BombZombie::zombiesLeft = 0;

// ------------------------------------------------------------------------------
//Métodos de criação

void BombZombie::createZombie() {	
	for (int i = 0; i < zombiesQnt; i++) {
		zombie = new Zombie(player, gridSet, zombiesXPos[i], zombiesYPos[i]);
		scene->Add(zombie, MOVING);
	}
}

void BombZombie::createHeart() {
	//criação dos corações
	h1 = new Heart(player, 1, 50.0f);
	scene->Add(h1, STATIC);

	h2 = new Heart(player, 2, 110.0f);
	scene->Add(h2, STATIC);

	h3 = new Heart(player, 3, 170.0f);
	scene->Add(h3, STATIC);
}
void BombZombie::createMap() {
	if (pseudoBoolean(mt) <= 0.2f) {
		// pano de fundo do jogo
		backg = new Background(CAMPO_DIA);
		scene->Add(backg, STATIC);

		//adiciona png de cerca na layer frontal
		fence = new Fence(CAMPO);
		scene->Add(fence, STATIC);

        mapa = 0;
	}
	else if(pseudoBoolean(mt) > 0.2f && pseudoBoolean(mt) <= 0.5f) {
		// pano de fundo do jogo
		backg = new Background(CEMITERIO_NOITE);
		scene->Add(backg, STATIC);

		//adiciona png de cerca na layer frontal
		fence = new Fence(CEMITERIO);
		scene->Add(fence, STATIC);

        mapa = 1;
	}
	else{
		// pano de fundo do jogo
		backg = new Background(FABRICA_DIA);
		scene->Add(backg, STATIC);

		//adiciona png de cerca na layer frontal
		fence = new Fence(FABRICA);
		scene->Add(fence, STATIC);

        mapa = 2;
	}
}
// -----------------------------------------------------------------------------

void BombZombie::Init()
{
    itensLeft = (uint)qntItens(mt);
    doorCreated = false;

	zombiesQnt = 7 + Engine::currentLvl;
	zombiesLeft = zombiesQnt;

    zombiesXPos = new uint[zombiesQnt];
    zombiesYPos = new uint[zombiesQnt];

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
                if ((pseudoBoolean(mt) >= 0.6f && !doorCreated) || (!doorCreated && index >= 80)) {
                    
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
    
    zombiesLeft = zombiesQnt;

    player = new Player(gridSet);
    scene->Add(player, MOVING);

	createZombie();

    createHeart();
    createMap();

    //criação do score
    score = new Score(player, 350, 60, mapa);
    scene->Add(score, STATIC);

}

// ------------------------------------------------------------------------------

void BombZombie::Update()
{
   
    // Entra na tela menu do jogo
    if (window->KeyDown(VK_ESCAPE))
    {
        Engine::Next<Home>();
    }
    else if (zombiesLeft == 0 && player->doorReached)
    {
        // Quantidade vida;
        Engine::values[0] = player->hp;
        // Quantidade pontos;
        Engine::values[1] += player->score;
        // Quantidade bombas;
        Engine::values[2] = player->bombsMax;
        // Quantidade tamanho da bomba;
        Engine::values[3] = player->bombSize;

        Engine::Next<NextLevel>();
    }
    else if (player->hp <= 0) // Vida menor que zero, player morre
    {
        // Quantidade vida;
        Engine::values[0] = player->hp;
        // Quantidade pontos;
        Engine::values[1] += player->score;
        // Quantidade bombas;
        Engine::values[2] = player->bombsMax;
        // Quantidade tamanho da bomba;
        Engine::values[3] = player->bombSize;

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
    //scene->DrawBBox();
} 

// ------------------------------------------------------------------------------

void BombZombie::Finalize()
{
    delete scene;
	delete zombiesXPos;
	delete zombiesYPos;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine* engine = new Engine();

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



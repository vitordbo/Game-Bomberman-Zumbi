#include "GameOver.h"
#include "Engine.h"
#include "BombZombie.h"
#include "Score.h"

void GameOver::Init()
{
	// tela de GAME OVER
	telaGameOver = new Sprite("Resources/GameOver.png");
	/*score = new Score(BombZombie::player, 60, 300);
	BombZombie::scene->Add(score, STATIC);*/
}


void GameOver::Update()
{
	if (window->KeyDown(VK_ESCAPE))
	{
		// Jogo fecha
		window->Close();
	}
	else if (window->KeyDown(VK_RETURN))
	{
		// Player sai da tela game over e volta para o nível UM
		Engine::currentLvl = 0;
		Engine::Next<BombZombie>();
	}
}

void GameOver::Draw()
{
	telaGameOver->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);

}

void GameOver::Finalize()
{
	delete telaGameOver;
	
}

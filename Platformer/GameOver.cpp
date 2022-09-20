#include "GameOver.h"
#include "Engine.h"
#include "BombZombie.h"
#include "Score.h"

void GameOver::Init()
{
	// tela de GAME OVER
	telaGameOver = new Sprite("Resources/GameOver.png");
	font = new Font("Resources/font.png");

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
	Color black(1.0f, 1.0f, 1.0f, 1.0f);
	string scoreText(std::to_string(Engine::values[0]));
	telaGameOver->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
	font->Draw(170, 300, "Score: " + scoreText, black, Layer::FRONT, 0.5f);
}

void GameOver::Finalize()
{
	delete telaGameOver;
	
}

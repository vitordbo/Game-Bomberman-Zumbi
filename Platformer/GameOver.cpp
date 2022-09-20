#include "GameOver.h"
#include "Engine.h"
#include "BombZombie.h"
#include "Score.h"

void GameOver::Init()
{
	// tela de GAME OVER
	telaGameOver = new Sprite("Resources/GameOver.png");
	font = new Font("Resources/font.png");

	//mão de select
	hand = new Sprite("Resources/hand.png");

	ctrlMove = true;

	handX = 250.0f;
	handY = 450.0f;

}


void GameOver::Update()
{
	if (ctrlMove && (window->KeyDown(VK_LEFT) || window->KeyDown(VK_RIGHT)))
	{
		if (handX == 250.0f)
			handX = 50.0f;
		else
			handX = 250.0f;

		ctrlMove = false;
	}
	else if (window->KeyUp(VK_LEFT) && window->KeyUp(VK_RIGHT))
	{
		ctrlMove = true;
	}
	if (window->KeyDown(VK_RETURN))
	{
		if (handX == 250.0f) {
			Engine::currentLvl = 0;
			Engine::Next<BombZombie>();
		}
		else
			window->Close();
	}
}

void GameOver::Draw()
{
	Color black(1.0f, 1.0f, 1.0f, 1.0f);
	string scoreText(std::to_string(Engine::values[1]));
	telaGameOver->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
	font->Draw(170, 300, "Score: " + scoreText, black, Layer::FRONT, 0.5f);
	hand->Draw(handX, handY);
}

void GameOver::Finalize()
{
	delete telaGameOver;
	delete hand;
	
}

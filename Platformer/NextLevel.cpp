#include "NextLevel.h"
#include "Engine.h"
#include "BombZombie.h"
#include "Player.h"
#include "Font.h"

void NextLevel::Init()
{
	// Tela Continue
	continuar = new Sprite("Resources/StageClear.png");
	font = new Font("Resources/font.png");

	
}

void NextLevel::Update()
{
	if (ctrlKeyESC && window->KeyDown(VK_ESCAPE))
	{
		// Jogo fecha
		ctrlKeyESC = false;
		window->Close();
	}

	if (window->KeyDown(VK_RETURN))
	{
		// Player sai da tela menu e volta para o nível que estava
		Engine::currentLvl++;
		Engine::Next<BombZombie>();
	}
}

void NextLevel::Draw()
{
	// desenha tela menu no jogo

	Color black(1.0f, 1.0f, 1.0f, 1.0f);
	string scoreText(std::to_string(Engine::values[0]));
	continuar->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
	font->Draw(170, 300, "Score: " + scoreText, black, Layer::FRONT, 0.5f);

}

void NextLevel::Finalize()
{
	delete continuar;
	delete font;
}
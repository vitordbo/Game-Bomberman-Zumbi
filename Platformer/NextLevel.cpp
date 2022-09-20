#include "NextLevel.h"
#include "Engine.h"
#include "BombZombie.h"

void NextLevel::Init()
{
	// Tela Continue
	continuar = new Sprite("Resources/StageClear.png");
}

void NextLevel::Finalize()
{
	delete continuar;
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
	continuar->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);

}
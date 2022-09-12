#include "Home.h"
#include "Engine.h"
#include "BombZombie.h"

void Home::Init()
{
	// Tela MENU
	menu = new Sprite("Resources/menu.png");
}

void Home::Finalize()
{
	delete menu;
}

void Home::Update()
{
	if (ctrlKeyESC && window->KeyDown(VK_ESCAPE))
	{
		// Jogo fecha
		ctrlKeyESC = false;
		window->Close();
	}
	else if (window->KeyUp(VK_ESCAPE))
	{
		// Player volta ao jogo
		ctrlKeyESC = true;
	}
	if (window->KeyDown(VK_RETURN))
	{
		// Player sai da tela menu e volta para o nível que estava
		Engine::Next<BombZombie>();
	}
}

void Home::Draw()
{
	// desenha tela menu no jogo
	menu->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);

}
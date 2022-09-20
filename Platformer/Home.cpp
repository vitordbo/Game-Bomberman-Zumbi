#include "Home.h"
#include "Engine.h"
#include "BombZombie.h"

void Home::Init()
{
	// Tela MENU
	menu = new Sprite("Resources/menu.png");
	
	//mão de select
	hand = new Sprite("Resources/hand.png");

	ctrlMove = true;

	handX = 290.0f;
	handY = 390.0f;
}

void Home::Finalize()
{
	delete menu;
	delete hand;
}

void Home::Update()
{
	if (ctrlMove && (window->KeyDown(VK_DOWN) || window->KeyDown(VK_UP)))
	{
		if (handY == 390.0f)
			handY = 460.0f;
		else
			handY = 390.0f;

		ctrlMove = false;
	}
	else if (window->KeyUp(VK_DOWN) && window->KeyUp(VK_UP))
	{
		ctrlMove = true;
	}
	if (window->KeyDown(VK_RETURN))
	{
		if (handY == 390.0f) {
			Engine::currentLvl = 0;
			Engine::Next<BombZombie>();
		}
		else
			window->Close();
	}
}

void Home::Draw()
{
	// desenha tela menu no jogo
	menu->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
	hand->Draw(handX, handY);
}
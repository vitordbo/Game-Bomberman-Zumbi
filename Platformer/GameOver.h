#include "Game.h"
#include "Sprite.h"
#include "Font.h"
#include "Score.h"



class GameOver : public Game
{
private:
	Sprite* telaGameOver = nullptr;
	Font* font = nullptr;
	
	Sprite* hand = nullptr;
	bool ctrlMove;

	float handX;
	float handY;

public:

	void Init();
	void Update();
	void Finalize();
	void Draw();
};
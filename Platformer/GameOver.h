#include "Game.h"
#include "Sprite.h"

class GameOver : public Game
{
private:
	Sprite* telaGameOver = nullptr;
public:
	void Init();
	void Update();
	void Finalize();
	void Draw();
};
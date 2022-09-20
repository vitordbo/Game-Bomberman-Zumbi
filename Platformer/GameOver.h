#include "Game.h"
#include "Sprite.h"
#include "Font.h"
#include "Score.h"



class GameOver : public Game
{
private:
	Sprite* telaGameOver = nullptr;
	//Font* font = nullptr;
	//Score* score = nullptr;
public:

	void Init();
	void Update();
	void Finalize();
	void Draw();
};
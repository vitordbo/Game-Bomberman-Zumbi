#include "Game.h"
#include "Sprite.h"

class Home : public Game
{
private:
	Sprite* menu = nullptr;
	bool ctrlKeyESC = false;
public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};



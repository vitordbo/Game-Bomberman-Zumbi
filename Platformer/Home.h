#include "Game.h"
#include "Sprite.h"

class Home : public Game
{
private:
	Sprite* menu = nullptr;
	Sprite* hand = nullptr;
	bool ctrlMove;

	float handX;
	float handY;
public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};



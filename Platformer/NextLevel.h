#ifndef _BOMBZOMBIE_NEXTLEVEL_H_
#define _BOMBZOMBIE_NEXTLEVEL_H_

#include "Game.h"
#include "Sprite.h"

class NextLevel : public Game
{
private:
	Sprite* continuar = nullptr;
	bool ctrlKeyESC = false;

public:

	void Init();
	void Update();
	void Draw();
	void Finalize();
};


#endif
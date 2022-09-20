#ifndef _BOMBZOMBIE_NEXTLEVEL_H_
#define _BOMBZOMBIE_NEXTLEVEL_H_

#include "Game.h"
#include "Sprite.h"
#include "Font.h"


class NextLevel : public Game
{
private:
	Sprite* continuar = nullptr;
	bool ctrlKeyESC = false;
	Font* font = nullptr;

public:

	void Init();
	void Update();
	void Draw();
	void Finalize();
};


#endif
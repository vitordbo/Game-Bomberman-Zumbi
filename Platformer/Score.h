/**********************************************************************************
// Background (Arquivo de Cabe�alho)
//
// Cria��o:     21 Abr 2012
// Atualiza��o: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Plano de fundo do jogo
//
**********************************************************************************/

#ifndef _BOMBZOMBIE_SCORE_H_
#define _BOMBZOMBIE_SCORE_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background � composto por sprites
#include "Player.h"
#include "Font.h"
#include <string>

using std::string;

// ---------------------------------------------------------------------------------

class Score : public Object
{
private:
	Font* font;                             // fundo est�tico   
	Player* player;
	
public:
	Score(Player* player);      // construtor
	~Score();                               // destrutor

	void Update();                          // atualiza��o do objeto
	void Draw();                            // desenho do objeto
};


// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline void Score::Draw()
{

	Color black(0.0f, 0.0f, 0.0f, 1.0f);
	string scoreText(std::to_string(player->score));
	font->Draw(350, 60, "Score: " + scoreText, black, Layer::FRONT, 1.5f);
	font->Spacing("Resources/consolas12.dat");

}

inline void Score::Update() {}
// ---------------------------------------------------------------------------------
#endif
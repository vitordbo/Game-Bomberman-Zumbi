/**********************************************************************************
// Background (Arquivo de Cabeçalho)
//
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plano de fundo do jogo
//
**********************************************************************************/

#ifndef _BOMBZOMBIE_SCORE_H_
#define _BOMBZOMBIE_SCORE_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background é composto por sprites
#include "Player.h"
#include "Font.h"
#include <string>

using std::string;

// ---------------------------------------------------------------------------------

class Score : public Object
{
private:
	Font* font;                             
	Player* player;
	
public:
	Score(Player* player, float posX, float posY, uint mapa);					// construtor
	~Score();								// destrutor

	float posX;
	float posY;
	uint mapa;

	void Update();                          // atualização do objeto
	void Draw();                            // desenho do objeto
};


// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Score::Draw()
{

	Color black(0.0f, 0.0f, 0.0f, 1.0f);
	Color white(1.0f, 1.0f, 1.0f, 1.0f);

	string scoreText(std::to_string(player->score));
	
	if(mapa == 1)
		font->Draw(posX, posY, "Score: " + scoreText, white, Layer::FRONT, 0.5f);
	else 
		font->Draw(posX, posY, "Score: " + scoreText, black, Layer::FRONT, 0.5f);
	
	font->Spacing("Resources/font.dat");

}

inline void Score::Update() {}
// ---------------------------------------------------------------------------------
#endif
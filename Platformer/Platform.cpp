/**********************************************************************************
// Platform (Código Fonte)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#include "Platform.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType)
{
    switch (platType)
    {
    case 0:
        platform = new Sprite("Resources/SmallGray.png");
        break;
    case 1:
        platform = new Sprite("Resources/MediumGray.png");
        break;
    case 2:
        platform = new Sprite("Resources/LongGray.png");
        break;
    }

    float x1 = -(platform->Width() / 2);
    float y1 = -(platform->Height() / 2);
    float x2 = (platform->Width() / 2);
    float y2 = (platform->Height() / 2);

    BBox(new Rect(x1, y1, x2, y2));
    MoveTo(posX, posY, 0.0f);

}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
    delete platform;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{
    Translate(-100.0f * gameTime, 0);
}

// -------------------------------------------------------------------------------

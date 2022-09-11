/**********************************************************************************
// Platform (Arquivo de Cabe�alho)
// 
// Cria��o:     21 Abr 2012
// Atualiza��o: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Plataformas do jogo
//
**********************************************************************************/

#ifndef _PLATFORMER_PLATFORM_H_
#define _PLATFORMER_PLATFORM_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background � composto por sprites

// ---------------------------------------------------------------------------------

enum PLATTYPES { SMALL, MEDIUM, LARGE };

// ---------------------------------------------------------------------------------

class Platform : public Object
{
private:
    Sprite * platform = nullptr;        // sprite da plataforma

public:
    Platform(float posX, float posY, uint platType);    
    ~Platform();

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
    float Width();
    float Height();
}; 

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline
inline void Platform::Draw()
{
    platform->Draw(x, y, z);
}

inline float Platform::Width()
{
    return (float)platform->Width();
}
inline float Platform::Height()
{
    return (float)platform->Height();
}
// ---------------------------------------------------------------------------------

#endif
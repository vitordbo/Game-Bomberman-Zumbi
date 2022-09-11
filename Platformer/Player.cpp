/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     20 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para o jogador
//
**********************************************************************************/

#include "Player.h"
#include "Platform.h"


// ---------------------------------------------------------------------------------

Player::Player()
{
    tileset = new TileSet("Resources/GravityGuy.png", 32, 48, 5, 10);
    anim = new Animation(tileset, 0.120f, true);

    uint SeqMove[4] = { 1, 2, 3, 4 };
    uint SeqMoveInv[4] = { 6, 7, 8, 9 };
    uint SeqIdle[1] = { 0 };
    uint SeqIdleInv[1] = { 5 };

    anim->Add(MOVE, SeqMove, 4);
    anim->Add(MOVE_INV, SeqMoveInv, 4);
    anim->Add(IDLE, SeqIdle, 1);
    anim->Add(IDLE_INV, SeqIdleInv, 1);

    float x1 = -14.0f;
    float y1 = -24.0f;
    float x2 = 15.0f;
    float y2 = 24.0f;

    BBox(new Rect(x1, y1, x2, y2));

    state = IDLE;
    falling = true;
    keyCtrl = true;

    MoveTo(window->CenterX(), 48.0f, 0.0f);
}


// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete tileset;
    delete anim;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    if (gravity == NORMAL)
        MoveTo(x, obj->Y() - 40.0);
    else
        MoveTo(x, obj->Y() + 40.0);
    falling = false;

}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    if ((y + 100) < 0) {
        MoveTo(x, window->Height());
        gravity = INVERTED;
    }

    if ((y - 100) > window->Height()) {
        MoveTo(x, 0.0f);
        gravity = NORMAL;
    }

    if (falling) {
        if (gravity == NORMAL) {

            state = IDLE;
            Translate(0, 200.0f * gameTime);
        }
        else if (gravity == INVERTED) {

            state = IDLE_INV;
            Translate(0, -200.0f * gameTime);
        }
    }
    else {
        if (keyCtrl && window->KeyDown(VK_SPACE)) {
            if (gravity == NORMAL) {
                MoveTo(x, y - 10.0f);
                gravity = INVERTED;
            }
            else if (gravity == INVERTED) {
                MoveTo(x, y + 10.0f);
                gravity = NORMAL;
            }
            keyCtrl = false;
        }
        else if (window->KeyUp(VK_SPACE))
            keyCtrl = true;

        if (gravity == INVERTED)
            state = MOVE_INV;
        else
            state = MOVE;
    }

    anim->Select(state);
    anim->NextFrame();
    falling = true;
}

// ---------------------------------------------------------------------------------
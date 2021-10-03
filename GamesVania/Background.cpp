/**********************************************************************************
// Background (Código Fonte)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plano de fundo do jogo
//
**********************************************************************************/

#include "Background.h"

// ---------------------------------------------------------------------------------
bool Background::stoped = false;

Background::Background(Color tint) : color(tint)
{
    MoveTo(window->CenterX(), window->CenterY(), Layer::BACK);
    xF = x;

    // carrega imagens
    imgF = new Image("Resources/camera.jpg");
    //imgB = new Image("Resources/BackgBack.png");

    // cria sprites do plano de fundo
    sky     = new Sprite("Resources/Sky.png");    
    backgF1 = new Sprite(imgF);
    //backgF2 = new Sprite(imgF);
    //backgB1 = new Sprite(imgB);
    //backgB2 = new Sprite(imgB);
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    delete imgF;
    delete imgB;    
    delete backgF1;
    delete backgF2;
    delete backgB1;
    delete backgB2;
    delete sky;
}

// -------------------------------------------------------------------------------
bool Background::Right() {
    if (xRight < 602) return true;
    else return false;
}

bool Background::Left() {
    if (xLeft > -2) return true;
    else return false;
}

void Background::Update()
{
    xRight = xF + imgF->Width() / 2.0f;
    xLeft = xF - imgF->Width() / 2.0f;
    // move sprites com velocidades diferentes
    //xF -= 200 * gameTime;
    //xB -= 150 * gameTime;
    if (!stoped) {
        if ((xF - imgF->Width() / 2.0f <= -2)) {
            if (window->KeyDown(VK_LEFT)) {
                xF += 200.0f * gameTime;
            }
        }
        else stoped = true;
        if ((xF + imgF->Width() / 2.0f >= 602)) {
            if (window->KeyDown(VK_RIGHT)) {
                xF -= 200.0f * gameTime;
            }
        }
        else stoped = true;
    }
}

// -------------------------------------------------------------------------------

void Background::Draw()
{
    // desenha pano de fundo
    sky->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 1.0f, 0.0f, color);

    // desenha prédios mais distantes
    //backgB1->Draw(xB, y, Layer::LOWER, 1.0f, 0.0f, color);
    //backgB2->Draw(xB + imgB->Width(), y, Layer::LOWER, 1.0f, 0.0f, color);
    
    // traz pano de fundo de volta para dentro da tela
    //if (xB + imgB->Width()/2.0f < 0)
    //    xB += imgB->Width();

    // desenha prédios mais próximos
    backgF1->Draw(xF, y, Layer::MIDDLE, 1.0f, 0.0f, color);
    //backgF2->Draw(xF + imgF->Width(), window->Height()/2.0f, Layer::MIDDLE, 1.0f, 0.0f, color);

    // traz pano de fundo de volta para dentro da tela
    //if (xF + imgF->Width()/2.0f < 0)
    //    xF += imgF->Width();
}

// -------------------------------------------------------------------------------

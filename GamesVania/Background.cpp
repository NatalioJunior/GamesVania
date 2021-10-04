
#include "Background.h"

// ---------------------------------------------------------------------------------
float Background::xLeft     = 0;
float Background::xRight    = 0;
bool Background::stoped     = false;

Background::Background(Color tint) : color(tint)
{
    MoveTo(window->CenterX(), window->CenterY(), Layer::BACK);
    // carrega imagens
    imgF = new Image("Resources/camera.jpg");

    // cria sprites do plano de fundo
    sky     = new Sprite("Resources/Sky.png");    
    backgF1 = new Sprite(imgF);

    xF = x;
    xRight = xF + imgF->Width() / 2.0f;
    xLeft = xF - imgF->Width() / 2.0f;
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    delete imgF;
    delete sky;
}

// -------------------------------------------------------------------------------
bool Background::Right() {
    if (xRight < 962) return true;
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
    if (!stoped) {
        if ((xF - imgF->Width() / 2.0f <= -2)) {
            if (window->KeyDown(VK_LEFT)) {
                xF += 200.0f * gameTime;
            }
        }
        else stoped = true;
        if ((xF + imgF->Width() / 2.0f >= 962)) {
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
    // desenha pano de fundo estático
    sky->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 1.0f, 0.0f, color);

    // desenha pano de fundo dinâmico
    backgF1->Draw(xF, y, Layer::MIDDLE, 1.0f, 0.0f, color);
}

// -------------------------------------------------------------------------------

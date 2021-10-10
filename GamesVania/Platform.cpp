/**********************************************************************************
// Platform (Código Fonte)
// 
// Criação:     21 Abr 2012
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#include "Platform.h"
#include "Background.h"
#include "GamesVania.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType, uint platBreadth, Color tint) : color(tint)
{
    switch (platType)
    {
    case MARIO:  
        switch (platBreadth)
        {
        case SMALL: platform = new Sprite("Resources/SmallPlat_Mario.png"); break;
        case MEDIUM: platform = new Sprite("Resources/MediumPlat_Mario.png"); break;
        case LONNG: platform = new Sprite("Resources/LongPlat_Mario.png"); break;
        case LARGE: platform = new Sprite("Resources/LargePlat_Mario.png"); break;
        }
        BBox(new Rect(-platform->Width() / 2.0f,
            -platform->Height() / 2.0f,
            platform->Width() / 2.0f,
            platform->Height() / 2.0f));
        PlatformType = MARIO;
        break;
        
    case TETRIS: 
        switch (platBreadth)
        {
        case SMALL: platform = new Sprite("Resources/SmallPlat_Tetris.png"); break;
        case MEDIUM: platform = new Sprite("Resources/MediumPlat_Tetris.png"); break;
        case LONNG: platform = new Sprite("Resources/LongPlat_Tetris.png"); break;
        case LARGE: platform = new Sprite("Resources/LargePlat_Tetris.png"); break;
        }
        BBox(new Rect(-platform->Width() / 2.0f,
            -platform->Height() / 2.0f,
            platform->Width() / 2.0f,
            platform->Height() / 2.0f));
        PlatformType = TETRIS;
        break;

    case PACMAN:  
        switch (platBreadth)
        {
        case SMALL: platform = new Sprite("Resources/SmallPlat_PacMan.png"); break;
        case MEDIUM: platform = new Sprite("Resources/MediumPlat_PacMan.png"); break;
        case LONNG: platform = new Sprite("Resources/LongPlat_PacMan.png"); break;
        case LARGE: platform = new Sprite("Resources/LargePlat_PacMan.png"); break;
        }
        BBox(new Rect(-platform->Width() / 2.0f + 10.0f,
            -platform->Height() / 2.0f,
            platform->Width() / 2.0f - 10.0f,
            platform->Height() / 2.0f));
        PlatformType = PACMAN;
        break;
    }

    MoveTo(posX, posY, Layer::MIDDLE);

    type = PLATFORM;
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
    delete platform;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{
    // move plataforma apenas no eixo x
    if (!Background::stoped) {
        if (window->KeyDown(VK_LEFT)) {
            Translate(200.0f * gameTime, 0);
        }
        if (window->KeyDown(VK_RIGHT)) {
            Translate(-200.0f * gameTime, 0);
        }
    }
}

// -------------------------------------------------------------------------------

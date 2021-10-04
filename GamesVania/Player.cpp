
#include "Player.h"
#include "LevelMaster.h"
#include "Platform.h"
#include "Background.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    tileset = new TileSet("Resources/GravityGuy.png", 32, 48, 5, 10);
    anim = new Animation(tileset, 0.120f, true);

    // sequências de animação do player
    uint invert[4] = {6,7,8,9};
    uint normal[4] = {1,2,3,4};

    anim->Add(INVERTED, invert, 4);
    anim->Add(NORMAL, normal, 4);

    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));
    
    // inicializa estado do player
    gravity = NORMAL;
    direction = LEFT;
    movement = STILL;
    level = 0;

    // posição inicial
    MoveTo(window->CenterX(), window->CenterY(), Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;    
}

// ---------------------------------------------------------------------------------

void Player::Reset()
{
    // volta ao estado inicial
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
    gravity = NORMAL;
    level = 0;
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    if (obj->Type() == FINISH)
    {
        // chegou ao final do nível
        level++;
    }
    else
    {
        // mantém personagem em cima da plataforma
        if (gravity == NORMAL)
            MoveTo(x, obj->Y() - 32);
        //else
        //    MoveTo(window->CenterX(), obj->Y() + 32);
    }

    // ----------------------------------------------------------
    // Processa teclas pressionadas
    // ----------------------------------------------------------
    // jogador só pode alterar a gravidade enquanto estiver
    // em cima de uma plataforma, não é possível a mudança no ar
    // ----------------------------------------------------------

    if (window->KeyPress(VK_SPACE))
    {
        gravity = !gravity;

        // toca efeito sonoro
        LevelMaster::audio->Play(TRANSITION);

        // tira player da plataforma para evitar 
        // detecção de colisão no quadro seguinte
        if (gravity == NORMAL)
            Translate(0, 12);
        else
            Translate(0 , -12);
    }
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    if (Background::Right()) {
        if (window->KeyDown(VK_RIGHT)) {
            Translate(130.0f * gameTime, 0);
        }
        if (window->KeyDown(VK_LEFT)) {
            Translate(-130.0f * gameTime, 0);
            if (x <= window->CenterX()) Background::stoped = false;
        }
    }
    
    if (Background::Left()) {
        if (window->KeyDown(VK_RIGHT)) {
            Translate(130.0f * gameTime, 0);
            if (x >= window->CenterX()) Background::stoped = false;
        }
        if (window->KeyDown(VK_LEFT)) {
            Translate(-130.0f * gameTime, 0);
        }
    }

    if (window->KeyPress('O')) Background::stoped = true;

    if (window->KeyPress('P')) Background::stoped = false;

    // ação da gravidade sobre o personagem
    //if (gravity == NORMAL)    
    //    Translate(0, 300 * gameTime);
    //else
    //    Translate(0, -300 * gameTime);

    // atualiza animação
    anim->Select(gravity);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------
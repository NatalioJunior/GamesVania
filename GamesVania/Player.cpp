
#include "Player.h"
#include "LevelMaster.h"
#include "Platform.h"
#include "Background.h"
#include "GamesVania.h"
#include "HitBox.h"

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
    MoveTo(32, window->CenterY() -225.0f, Layer::FRONT);

    type = PLAYER;
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
    MoveTo(32, window->CenterY() - 225.0f, Layer::FRONT);
    hiting = false;
    jumping = false;
    jumpTimer.Reset();
    velY = 0;
    //gravity = NORMAL;
    //level = 0;
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    if (obj->Type() == PLATFORM) {
        Platform* p = (Platform*)obj;
        if (!jumping) {
            switch (p->PlatformType)
            {
            case PACMAN: 
                if (((Bottom() - 2.0f) - p->Top() >= -15.5f && (Bottom() - 2.0f) - p->Top() <= 15.5f)) {
                    MoveTo(x, p->Y() - 45.0f);
                }
                break;

            case MARIO:
                if (((Bottom()) - p->Top() >= -22.0f && (Bottom()) - p->Top() <= 22.0f)) {
                    MoveTo(x, p->Y() - 42.5f);
                }
                break;

            case TETRIS:
                if (((Bottom()) - p->Top() >= -20.0f && (Bottom()) - p->Top() <= 20.0f)) {
                    MoveTo(x, p->Y() - 46.8f);
                }

            }
            if (!hiting) {
                if (window->KeyDown(VK_DOWN)) {
                    Translate(0, 130.0f * gameTime);
                }
                if (window->KeyPress(VK_UP)) {
                    LevelMaster::audio->Play(TRANSITION);
                    jumping = true;
                    velY = -580.0f;
                    jumpTimer.Start();
                }
            }
        }
    }

    if (window->KeyPress('O')) {
        Background::stoped = true;
    }

}

// ---------------------------------------------------------------------------------

void Player::Update()
{

    if (!hiting) {
        if (window->KeyDown(VK_RIGHT)) {
            if (!jumping) movement = WALKING;
            direction = RIGHT;
        }
        if (window->KeyDown(VK_LEFT)) {
            if (!jumping) movement = WALKING;
            direction = LEFT;
        }

        if (Background::Right()) {
            if (window->KeyDown(VK_RIGHT)) {
                velX = 130.0f;
                Translate(130.0f * gameTime, 0);
            }
            if (window->KeyDown(VK_LEFT)) {
                velX = -130.0f;
                Translate(-130.0f * gameTime, 0);
                if (x <= window->CenterX()) Background::stoped = false;
            }
        }

        if (Background::Left()) {
            if (window->KeyDown(VK_RIGHT)) {
                velX = 130.0f;
                Translate(130.0f * gameTime, 0);
                if (x >= window->CenterX()) Background::stoped = false;
            }
            if (window->KeyDown(VK_LEFT)) {
                velX = -130.0f;
                Translate(-130.0f * gameTime, 0);
            }
        }

        if (window->KeyPress(VK_SPACE)) {
            hiting = true;
            HitBox* hitbox = new HitBox();
            LevelMaster::scene->Add(hitbox, MOVING);
        }
    }
    
    if (jumpTimer.Elapsed(0.75f)) velX = 0;
    else if ((Background::Right() || Background::Left()) && hiting) Translate(velX * gameTime, 0);
    
    if (jumping) {
        if (jumpTimer.Elapsed(0.5f)) {
            velY = 400.0f;
            jumping = false;
        }
        else {
            velY += 1570.0f * gameTime;
        }
    }
    else velY = 400.0f;

    Translate(0, velY * gameTime);
    if (window->KeyPress('P')) Background::stoped = false;

    if (x <= 16) MoveTo(16.0f, y);
    if (x >= 944) MoveTo(944, y);

    // atualiza animação
    anim->Select(gravity);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------
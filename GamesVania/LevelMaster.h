#ifndef _GAMESVANIA_LEVELMASTER_
#define _GAMESVANIA_LEVELMASTER_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Player.h"
#include "Scene.h"
#include "Background.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

enum Sounds { MENU, MUSIC, TRANSITION };

// ------------------------------------------------------------------------------

class LevelMaster : public Game
{
private:
    static Game* level;             // n�vel atual do jogo

public:
    static Player* player;          // jogador 
    static Audio* audio;            // sistema de �udio
    static Scene* scene;            // cena do jogo
    static bool viewBBox;           // estado da bounding box

    void Init();                    // inicializa jogo
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo

    template<class T>
    static void NextLevel()         // muda para pr�ximo n�vel do jogo
    {
        if (level)
        {
            level->Finalize();
            delete level;
            level = new T();
            level->Init();
        }
    };
};

// ---------------------------------------------------------------------------------

class Home : public Game
{
private:
    Sprite* backg = nullptr;        // pano de fundo
    TileSet* tileset = nullptr;     // tileset da anima��o
    Animation* anim = nullptr;      // anima��o do menu

public:
    void Init();                    // inicia n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza n�vel
};

// ------------------------------------------------------------------------------

class Level1 : public LevelMaster
{
private:
    Background* backg = nullptr;    // pano de fundo animado
    Scene* scene      = nullptr;    // cena do n�vel

public:

    void Init();                    // inicializa��o do n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza��o do n�vel
};

// -----------------------------------------------------------------------------

class Level2 : public LevelMaster
{
private:
    Background* backg = nullptr;   // pano de fundo animado
    Scene* scene      = nullptr;   // cena do n�vel

public:

    void Init();                    // inicializa��o do n�vel
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza��o do n�vel
};

// -----------------------------------------------------------------------------

class GameOver : public Game
{
private:
    Sprite* title = nullptr;        // tela de fim

public:
    void Init();                    // inicializa��o do n�vel
    void Update();                  // l�gica da tela de fim
    void Draw();                    // desenho da tela
    void Finalize();                // finaliza��o do n�vel
};

// ------------------------------------------------------------------------------

#endif

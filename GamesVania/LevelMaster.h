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
    static Game* level;             // nível atual do jogo

public:
    static Player* player;          // jogador 
    static Audio* audio;            // sistema de áudio
    static Scene* scene;            // cena do jogo
    static bool viewBBox;           // estado da bounding box

    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo

    template<class T>
    static void NextLevel()         // muda para próximo nível do jogo
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
    TileSet* tileset = nullptr;     // tileset da animação
    Animation* anim = nullptr;      // animação do menu

public:
    void Init();                    // inicia nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza nível
};

// ------------------------------------------------------------------------------

class Level1 : public LevelMaster
{
private:
    Background* backg = nullptr;    // pano de fundo animado
    Scene* scene      = nullptr;    // cena do nível

public:

    void Init();                    // inicialização do nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finalização do nível
};

// -----------------------------------------------------------------------------

class Level2 : public LevelMaster
{
private:
    Background* backg = nullptr;   // pano de fundo animado
    Scene* scene      = nullptr;   // cena do nível

public:

    void Init();                    // inicialização do nível
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finalização do nível
};

// -----------------------------------------------------------------------------

class GameOver : public Game
{
private:
    Sprite* title = nullptr;        // tela de fim

public:
    void Init();                    // inicialização do nível
    void Update();                  // lógica da tela de fim
    void Draw();                    // desenho da tela
    void Finalize();                // finalização do nível
};

// ------------------------------------------------------------------------------

#endif

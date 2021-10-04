#include "LevelMaster.h"

#include "Platform.h"
#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------

// inicializa membros estáticos da classe
Game* LevelMaster::level = nullptr;
Player* LevelMaster::player = nullptr;
Audio* LevelMaster::audio = nullptr;
Scene* LevelMaster::scene = nullptr;
bool    LevelMaster::viewBBox = false;

// ------------------------------------------------------------------------------
//                                  LevelMaster
// ------------------------------------------------------------------------------
void LevelMaster::Init()
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(MENU, "Resources/Menu.wav");
    audio->Add(MUSIC, "Resources/Music.wav");
    audio->Add(TRANSITION, "Resources/Transition.wav");

    // bounding box não visível
    viewBBox = false;

    // cria jogador
    player = new Player();

    // inicializa nível de abertura do jogo
    level = new Home();
    level->Init();
}

// ------------------------------------------------------------------------------

void LevelMaster::Update()
{
    // habilita/desabilita visualização da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // atualiza nível
    level->Update();
}

// ------------------------------------------------------------------------------

void LevelMaster::Draw()
{
    // desenha nível
    level->Draw();
}

// ------------------------------------------------------------------------------

void LevelMaster::Finalize()
{
    level->Finalize();

    delete player;
    delete audio;
    delete level;
}

// ------------------------------------------------------------------------------
//                                  Home
// ------------------------------------------------------------------------------
void Home::Init()
{
    backg = new Sprite("Resources/TitleScreen.png");
    tileset = new TileSet("Resources/PressEnter.png", 72, 48, 1, 5);
    anim = new Animation(tileset, 0.180f, true);
    LevelMaster::audio->Play(MENU, true);
}

// ------------------------------------------------------------------------------

void Home::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // se a tecla ENTER for pressionada
    if (window->KeyPress(VK_RETURN))
    {
        LevelMaster::audio->Stop(MENU);
        LevelMaster::NextLevel<Level1>();
    }
    else
    {
        anim->NextFrame();
    }
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    anim->Draw(545, 275);
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete anim;
    delete tileset;
    delete backg;
}

// ------------------------------------------------------------------------------
//                                  Level1
// ------------------------------------------------------------------------------
void Level1::Init()
{
    // cria gerenciador de cena
    scene = new Scene();
    LevelMaster::scene = scene;

    // pano de fundo do jogo
    backg = new Background(Color{ 1,1,1,1 });
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(LevelMaster::player, MOVING);

    // ----------------------
    // plataformas
    // ----------------------

    Platform* plat;
    float posX, posY;
    uint  platType;
    Color white{ 1,1,1,1 };

    ifstream fin;
    fin.open("Level1.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // lê linha com informações da plataforma
            fin >> posY; fin >> platType;
            plat = new Platform(posX, posY, platType, white);
            scene->Add(plat, STATIC);
        }
        else
        {
            // ignora comentários
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }

        fin >> posX;
    }
    fin.close();

    // ----------------------

    // inicia com música
    LevelMaster::audio->Frequency(MUSIC, 0.94f);
    LevelMaster::audio->Frequency(TRANSITION, 1.0f);
    LevelMaster::audio->Play(MUSIC);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
    if (window->KeyPress(VK_ESCAPE))
    {
        LevelMaster::audio->Stop(MUSIC);
        LevelMaster::NextLevel<Home>();
        LevelMaster::player->Reset();
    }
    else if (LevelMaster::player->Bottom() < 0 || LevelMaster::player->Top() > window->Height())
    {
        LevelMaster::audio->Stop(MUSIC);
        LevelMaster::NextLevel<GameOver>();
        LevelMaster::player->Reset();

    }
    else if (LevelMaster::player->Level() == 1 || window->KeyPress('N'))
    {
        LevelMaster::NextLevel<Level2>();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    backg->Draw();
    scene->Draw();

    if (LevelMaster::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    scene->Remove(LevelMaster::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
//                                  Level2
// ------------------------------------------------------------------------------
void Level2::Init()
{
    // cria gerenciador de cena
    scene = new Scene();
    LevelMaster::scene = scene;

    // pano de fundo do jogo
    Color dark{ 0.4f, 0.4f, 0.4f, 1.0f };
    backg = new Background(dark);
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(LevelMaster::player, MOVING);

    // ----------------------
    // plataformas
    // ----------------------

    Platform* plat;
    float posX, posY;
    uint  platType;

    ifstream fin;
    fin.open("Level2.txt");

    fin >> posX;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // lê linha com informações da plataforma
            fin >> posY; fin >> platType;
            plat = new Platform(posX, posY, platType, dark);
            scene->Add(plat, STATIC);
        }
        else
        {
            // ignora comentários
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }

        fin >> posX;
    }
    fin.close();

    // ----------------------

    LevelMaster::audio->Frequency(MUSIC, 1.0f);
    LevelMaster::audio->Frequency(TRANSITION, 0.85f);
}

// ------------------------------------------------------------------------------

void Level2::Update()
{
    if (window->KeyPress(VK_ESCAPE) || LevelMaster::player->Level() == 2 || window->KeyPress('N'))
    {
        LevelMaster::audio->Stop(MUSIC);
        LevelMaster::NextLevel<Home>();
        LevelMaster::player->Reset();
    }
    else if (LevelMaster::player->Bottom() < 0 || LevelMaster::player->Top() > window->Height())
    {
        LevelMaster::audio->Stop(MUSIC);
        LevelMaster::NextLevel<GameOver>();
        LevelMaster::player->Reset();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
}

// ------------------------------------------------------------------------------

void Level2::Draw()
{
    backg->Draw();
    scene->Draw();

    if (LevelMaster::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level2::Finalize()
{
    scene->Remove(LevelMaster::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
//                                  GameOver
// ------------------------------------------------------------------------------
void GameOver::Init()
{
    title = new Sprite("Resources/GameOver.png");
}

// ----------------------------------------------------------------------

void GameOver::Update()
{
    if (window->KeyPress(VK_ESCAPE) || window->KeyPress(VK_RETURN))
        LevelMaster::NextLevel<Home>();
}

// ----------------------------------------------------------------------

void GameOver::Draw()
{
    title->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

// ----------------------------------------------------------------------

void GameOver::Finalize()
{
    delete title;
}

// ----------------------------------------------------------------------
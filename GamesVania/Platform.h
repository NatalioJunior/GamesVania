
#ifndef _GAMESVANIA_PLATFORM_H_
#define _GAMESVANIA_PLATFORM_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites

// ---------------------------------------------------------------------------------

enum PLATBREADTH { SMALL, MEDIUM, LONNG, LARGE };
enum PLATTYPE    { MARIO, TETRIS, PACMAN };

// ---------------------------------------------------------------------------------

class Platform : public Object
{
private:
    Sprite * platform = nullptr;            // sprite da plataforma
    Color color;                            // cor da plataforma

public:
    uint PlatformType = 0;
    Platform(float posX, float posY, 
             uint platType,
             uint platBreadth,
             Color tint);                   // construtor    
    ~Platform();                            // destrutor

    float Top();
    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
}; 

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Platform::Draw()
{ platform->Draw(x, y, z, 1.0f, 0.0f, color); }

inline float Platform::Top()
{ return y - platform->Height() / 2; }

// ---------------------------------------------------------------------------------

#endif
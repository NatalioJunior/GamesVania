
#ifndef _GAMESVANIA_BACKGROUND_H_
#define _GAMESVANIA_BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background é composto por sprites

// ---------------------------------------------------------------------------------

class Background : public Object
{
private:
    static float xRight, xLeft;         // posição horizontal extrema dos sprites
    float xF;                           // posição do eixo X;

    Image   * imgF;                     // imagem de fundo
    Sprite  * sky;                      // fundo estático
    Sprite  * backgF1;                  // pano de fundo dinâmico

    Color color;                        // cor do pano de fundo

public:
    static bool stoped;                 // quando a tela para na parte extrema esquerda ou extrema direita;
    Background(Color tint);             // construtor
    ~Background();                      // destrutor

    static bool Right();
    static bool Left();

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
}; 

// ---------------------------------------------------------------------------------

#endif

#ifndef _GAMESVANIA_BACKGROUND_H_
#define _GAMESVANIA_BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background � composto por sprites

// ---------------------------------------------------------------------------------

class Background : public Object
{
private:
    static float xRight, xLeft;         // posi��o horizontal extrema dos sprites
    float xF;                           // posi��o do eixo X;

    Image   * imgF;                     // imagem de fundo
    Sprite  * sky;                      // fundo est�tico
    Sprite  * backgF1;                  // pano de fundo din�mico

    Color color;                        // cor do pano de fundo

public:
    static bool stoped;                 // quando a tela para na parte extrema esquerda ou extrema direita;
    Background(Color tint);             // construtor
    ~Background();                      // destrutor

    static bool Right();
    static bool Left();

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
}; 

// ---------------------------------------------------------------------------------

#endif
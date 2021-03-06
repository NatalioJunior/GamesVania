
#ifndef _GAMESVANIA_PLAYER_H_
#define _GAMESVANIA_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus?es

#include "Types.h"                      // tipos espec?ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima??o de sprites
#include "Timer.h"

// ------------------------------------------------------------------------------

enum Direction  {LEFT, RIGHT};
enum Movement   { STILL, WALKING };
enum Gravity    {NORMAL, INVERTED};

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet   * tileset;                // folha de sprites do personagem
    Animation * anim;                   // anima??o do personagem
    uint        movement;               // movimento que o player est? realizando
    uint        gravity;
    int         level;                  // n?vel finalizado

    Timer       jumpTimer;
    bool        jumping = false;
    float       velY    = 0;
    float       velX    = 0;
    
public:
    bool        hiting  = false;
    uint        direction;              // dire??o que o player est? seguindo

    Player();                           // construtor
    ~Player();                          // destrutor

    void Reset();                       // volta ao estado inicial
    int Level();                        // ?ltimo n?vel finalizado
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo

    void OnCollision(Object * obj);     // resolu??o da colis?o
    void Update();                      // atualiza??o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun??o Membro Inline

inline int Player::Level()
{ return level; }

inline float Player::Bottom()
{ return y + tileset->Height()/4; }

inline float Player::Top()
{ return y - tileset->Height()/2; }

inline void Player::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif
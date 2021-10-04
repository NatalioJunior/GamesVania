
#ifndef _GAMESVANIA_PLAYER_H_
#define _GAMESVANIA_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites

// ------------------------------------------------------------------------------

enum Direction  {LEFT, RIGHT};
enum Movement   {STILL, WALKING, JUMPING, CROUCHED, HITING};
enum Gravity    {NORMAL, INVERTED};

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet   * tileset;                // folha de sprites do personagem
    Animation * anim;                   // animação do personagem
    uint        movement;               // movimento que o player está realizando
    uint        gravity;
    int         level;                  // nível finalizado
    
public:
    uint        direction;              // direção que o player está seguindo

    Player();                           // construtor
    ~Player();                          // destrutor

    void Reset();                       // volta ao estado inicial
    int Level();                        // último nível finalizado
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo

    void OnCollision(Object * obj);     // resolução da colisão
    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline int Player::Level()
{ return level; }

inline float Player::Bottom()
{ return y + tileset->Height()/2; }

inline float Player::Top()
{ return y - tileset->Height()/2; }

inline void Player::Draw()
{ anim->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif
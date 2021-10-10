#ifndef _HIT_BOX_H_
#define _HIT_BOX_H_

// ---------------------------------------------------------------------------------
#include "Object.h"
#include "Timer.h"

// ---------------------------------------------------------------------------------

class HitBox : public Object {
private:
	const float velX	= 50.0f;
	Timer		LifeTime;
	uint		PlayerDirection;

public:
	HitBox();
	~HitBox();

	void Update();
	void Draw();

};
// ---------------------------------------------------------------------------------
// Função Membro Inline
inline HitBox::~HitBox() {}
inline void HitBox::Draw() {};

#endif
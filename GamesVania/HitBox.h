#include "Object.h"
#include "Scene.h"
#include "Player.h"

class HitBox : public Object {
private:
	const float LifeTime = 1.5f;
	const float velX = 150.0f;
	uint PlayerDirection;
	Scene* scene = nullptr;
	Player* player = nullptr;

public:
	HitBox();
	~HitBox();

	void Update();
	void Draw();

};
// ---------------------------------------------------------------------------------
// Função Membro Inline
inline HitBox::~HitBox() {};
inline void HitBox::Draw() {};
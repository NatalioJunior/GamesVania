#include "HitBox.h"
#include "LevelMaster.h"

HitBox::HitBox() {
	scene = LevelMaster::scene;
	player = LevelMaster::player;
	PlayerDirection = player->direction;
	BBox(new Rect(-13, -5, 13, 5));
	MoveTo(player->X(), player->Y() - 10.0f);
}

void HitBox::Update() {
	if (PlayerDirection == LEFT)
		Translate(-300.0f * gameTime, 0);
	else Translate(300.0f * gameTime, 0);
}
#include "HitBox.h"
#include "LevelMaster.h"
#include "GamesVania.h"

HitBox::HitBox() {
	//LEFT = 0 | RIGHT = 1
	PlayerDirection = LevelMaster::player->direction;
	BBox(new Rect(0, 0, 30.0f, 10.0f));
	if (PlayerDirection) MoveTo(LevelMaster::player->X() + 16.0f, LevelMaster::player->Y() - 10.0f);
	else MoveTo(LevelMaster::player->X() - 46.0f, LevelMaster::player->Y() - 10.0f);
	type = HITBOX;

	LifeTime.Start();
}

void HitBox::Update() {
	if (PlayerDirection) MoveTo(LevelMaster::player->X() + 16.0f, LevelMaster::player->Y() - 10.0f);
	else MoveTo(LevelMaster::player->X() - 46.0f, LevelMaster::player->Y() - 10.0f);

	if (LifeTime.Elapsed(0.55f)) {
		LevelMaster::player->hiting = false;
		LevelMaster::scene->Delete(this, MOVING);

	}
}

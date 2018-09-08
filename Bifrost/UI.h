#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Text.h"

class UI : public Entity
{
public:
	UI();
	~UI();
	Sprite *info;
	Sprite *hp;
	Sprite *mp;
	Sprite *skillQCooltime;
	Sprite *skillWCooltime;
	Sprite *skillECooltime;
	Sprite *itemList[6];
	Sprite *white;
	Sprite *black;
	Sprite *shop;
	Sprite *shopBack;
	Sprite *buyBtn[2][3];
	Sprite *scoreBoad;
	Sprite *breakTower;
	Sprite *brokenTower;
	Sprite *kill;
	Sprite *die;
	Text *moneyText;
	Text *timeText;
	Text *powerText;
	Text *armorText;
	Text *speedText;
	Text *whiteScoreText;
	Text *blackScoreText; 
};


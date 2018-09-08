#include "DXUT.h"
#include "UI.h"
#include "GameManager.h"

UI::UI()
{
	addChild(die = new Sprite("image/UI/text/die.png"));
	die->visible = false;

	if (gameManager.isKnight)
	{
		addChild(info = new Sprite("image/UI/ingame/info/knight.png"));
	}
	else
	{
		addChild(info = new Sprite("image/UI/ingame/info/evil.png"));
	}

	addChild(skillQCooltime = new Sprite("image/UI/ingame/skillcooltime.png"));
	skillQCooltime->pos = Vec2(620, 650);
	addChild(skillWCooltime = new Sprite("image/UI/ingame/skillcooltime.png"));
	skillWCooltime->pos = Vec2(684, 650);
	addChild(skillECooltime = new Sprite("image/UI/ingame/skillcooltime.png"));
	skillECooltime->pos = Vec2(744, 650);

	addChild(hp = new Sprite("image/UI/ingame/hpbar.png"));
	hp->pos = Vec2(598, 695);
	addChild(mp = new Sprite("image/UI/ingame/mpbar.png"));
	mp->pos = Vec2(598, 707);

	addChild(scoreBoad = new Sprite("image/UI/ingame/all.png"));

	addChild(powerText = new Text("100", 20, D3DXCOLOR(1, 1, 1, 1)));
	powerText->pos = Vec2(441, 652);
	addChild(armorText = new Text("100", 20, D3DXCOLOR(1, 1, 1, 1)));
	armorText->pos = Vec2(441, 675);
	addChild(speedText = new Text("100", 20, D3DXCOLOR(1, 1, 1, 1)));
	speedText->pos = Vec2(441, 698);

	addChild(breakTower = new Sprite("image/UI/text/asdf2.png"));
	breakTower->pos = Vec2(407, 110);
	breakTower->visible = false;
	addChild(brokenTower = new Sprite("image/UI/text/asdf1.png"));
	brokenTower->pos = Vec2(390, 110);
	brokenTower->visible = false;
	addChild(kill = new Sprite("image/UI/text/kill.png"));
	kill->pos = Vec2(468, 110);
	kill->visible = false;

	addChild(white = new Sprite("image/UI/ingame/minimap/knight.png"));
	addChild(black = new Sprite("image/UI/ingame/minimap/evil.png"));

	addChild(moneyText = new Text("123", 20, D3DXCOLOR(1, 1, 1, 1)));
	moneyText->pos = Vec2(880, 620);

	addChild(timeText = new Text("00:00", 30, D3DXCOLOR(1, 1, 1, 1)));
	timeText->pos = Vec2(645, 18);
	addChild(whiteScoreText = new Text("0", 30, D3DXCOLOR(1, 168 / 255.0f, 46 / 255.0f, 1)));
	whiteScoreText->pos = Vec2(552, 8);
	addChild(blackScoreText = new Text("0", 30, D3DXCOLOR(1, 88 / 255.0f, 59 / 255.0f, 1)));
	blackScoreText->pos = Vec2(799, 8);

	addChild(itemList[0] = new Sprite("image/UI/shop/item/hp.png"));
	addChild(itemList[1] = new Sprite("image/UI/shop/item/mp.png"));
	addChild(itemList[2] = new Sprite("image/UI/shop/item/skill.png")); 
	addChild(itemList[3] = new Sprite("image/UI/shop/item/attackpower.png"));
	addChild(itemList[4] = new Sprite("image/UI/shop/item/sheild.png"));
	addChild(itemList[5] = new Sprite("image/UI/shop/item/move.png"));
	itemList[0]->visible = false;
	itemList[1]->visible = false;
	itemList[2]->visible = false;
	itemList[3]->visible = false;
	itemList[4]->visible = false;
	itemList[5]->visible = false;

	addChild(shopBack = new Sprite("image/UI/shop/shopbg.png"));
	shopBack->visible = false;
	addChild(shop = new Sprite("image/UI/shop/shop.png"));
	shop->pos = Vec2(351, 23);
	shop->visible = false;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			addChild(buyBtn[i][j] = new Sprite("image/UI/shop/buy1.png"));
			buyBtn[i][j]->visible = false;
			buyBtn[i][j]->pos = Vec2(570 + i * 280, 220 + j * 165);
		}
	}
}

UI::~UI()
{
}

#include "DXUT.h"
#include "Minion.h"
#include "MuldirAnimation.h"

Minion::Minion(TeamType team)
{
	this->team = team;
	type = MINION;
	colPivot = Vec2(97, 117);
	colRange = 25;
	attackRange = 35;
	scanRange = 250;
	speed = 150;
	backSpeed = 150;
	isAI = true;
	power = 5;
	hp = 100;
	maxHp = 100;

	if (team == WHITE)
	{
		addChild(animation[WALK] = new MuldirAnimation(this, "image/minion/knightMinion/nomalMinion/walk", 8));
		rect = animation[WALK]->rect;
		addChild(animation[DEAD] = new MuldirAnimation(this, "image/minion/knightMinion/nomalMinion/dead", 5, 5, false));
		animation[DEAD]->visible = false;
		((MuldirAnimation*)animation[DEAD])->Stop();
		addChild(animation[ATTACK] = new MuldirAnimation(this, "image/minion/knightMinion/nomalMinion/attack", 17));
		((MuldirAnimation*)animation[ATTACK])->Stop();
		animation[ATTACK]->visible = false;
		attackFrame = 5;
		attackFrame2 = 11;
		addChild(mindControl = new Sprite("image/evil/effect/skill3.png")); 
		mindControl->pos = Vec2(73, 0);
		mindControl->visible = false;
		addChild(hpBack = new Sprite("image/UI/hpbar/minion/knight/knightMinionHPbar1.png"));
		addChild(hpBar = new Sprite("image/UI/hpbar/minion/knight/knightMinionHPbar2.png"));
		hpBack->pos = Vec2(67, 32);
		hpBar->pos = Vec2(68, 33);
	}
	else if (team == BLACK)
	{
		addChild(animation[WALK] = new MuldirAnimation(this, "image/minion/evilminion/nomalMinion/walk", 8));
		rect = animation[WALK]->rect;
		addChild(animation[DEAD] = new MuldirAnimation(this, "image/minion/evilminion/nomalMinion/dead", 5, 5, false));
		animation[DEAD]->visible = false;
		((MuldirAnimation*)animation[DEAD])->Stop();
		addChild(animation[ATTACK] = new MuldirAnimation(this, "image/minion/evilminion/nomalMinion/attack", 15));
		animation[ATTACK]->visible = false;
		((MuldirAnimation*)animation[ATTACK])->Stop();
		attackFrame = 5;
		attackFrame2 = 10;
		addChild(hpBack = new Sprite("image/UI/hpbar/minion/evil/evilMinionHpbar1.png"));
		addChild(hpBar = new Sprite("image/UI/hpbar/minion/evil/evilMinionHpbar2.png"));
		hpBack->pos = Vec2(67, 32);
		hpBar->pos = Vec2(68, 33);
	}
}

Minion::~Minion()
{
}

SpecialMinion::SpecialMinion(TeamType team)
{
	this->team = team;
	type = MINION;
	colPivot = Vec2(125, 125);
	scanRange = 300;
	attackRange = 250;
	colRange = 35;
	power = 15;
	speed = 150;
	backSpeed = 150;

	hp = 120;
	maxHp = 120;

	isAI = true;

	if (team == WHITE)
	{
		addChild(animation[WALK] = new MuldirAnimation(this, "image/minion/knightMinion/specialMinion/walk", 6));
		rect = animation[WALK]->rect;
		addChild(animation[DEAD] = new MuldirAnimation(this, "image/minion/knightMinion/specialMinion/dead", 5, 5, false));
		animation[DEAD]->visible = false;
		((MuldirAnimation*)animation[DEAD])->Stop();
		addChild(animation[ATTACK] = new MuldirAnimation(this, "image/minion/knightMinion/specialMinion/attack", 10));
		animation[ATTACK]->visible = false;
		((MuldirAnimation*)animation[ATTACK])->Stop();
		attackFrame = 6;
		isLongAttack = true;
		addChild(mindControl = new Sprite("image/evil/effect/skill3.png"));
		mindControl->pos = Vec2(100, 6);
		mindControl->visible = false;
		addChild(hpBack = new Sprite("image/UI/hpbar/minion/knight/knightMinionHPbar1.png"));
		addChild(hpBar = new Sprite("image/UI/hpbar/minion/knight/knightMinionHPbar2.png"));
		hpBack->pos = Vec2(94, 43);
		hpBar->pos = Vec2(95, 44);
	}
	else if (team == BLACK)
	{
		addChild(animation[WALK] = new MuldirAnimation(this, "image/minion/evilminion/specialMinion/walk", 6));
		rect = animation[WALK]->rect;
		addChild(animation[DEAD] = new MuldirAnimation(this, "image/minion/evilminion/specialMinion/dead", 5, 5, false));
		animation[DEAD]->visible = false;
		((MuldirAnimation*)animation[DEAD])->Stop();
		addChild(animation[ATTACK] = new MuldirAnimation(this, "image/minion/evilminion/specialMinion/attack", 10));
		animation[ATTACK]->visible = false;
		((MuldirAnimation*)animation[ATTACK])->Stop();
		attackFrame = 6;
		isLongAttack = true;
		addChild(hpBack = new Sprite("image/UI/hpbar/minion/evil/evilMinionHpbar1.png"));
		addChild(hpBar = new Sprite("image/UI/hpbar/minion/evil/evilMinionHpbar2.png"));
		hpBack->pos = Vec2(94, 43);
		hpBar->pos = Vec2(95, 44);
	}
}

SpecialMinion::~SpecialMinion()
{

}
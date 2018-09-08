#include "DXUT.h"
#include "Nexus.h"
#include "World.h"
#include "GameScene.h"
#include "Hero.h"

Nexus::Nexus(TeamType type)
{
	this->type = NEXUS;
	this->team = type;
	if (team == WHITE)
	{
		addChild(animation = new Animation("image/map/knightnexus", 10));
		addChild(hpBack = new Sprite("image/UI/hpbar/nexus/knightNexusHpbar1.png"));
		addChild(hpBar = new Sprite("image/UI/hpbar/nexus/knightNexusHpbar2.png"));
		hpBack->pos = Vec2(113, 0);
		hpBar->pos = Vec2(116, 3);
	}
	else if (team == BLACK)
	{
		addChild(animation = new Animation("image/map/evilnexus", 10));
		addChild(hpBack = new Sprite("image/UI/hpbar/nexus/evilNexusHpbar1.png"));
		addChild(hpBar = new Sprite("image/UI/hpbar/nexus/evilNexusHpbar2.png"));
		hpBack->pos = Vec2(96, 569);
		hpBar->pos = Vec2(99, 572);
	}

	rect = animation->rect;
	colPivot = Vec2(306, 354);
	colRange = 250;
	
	hp = 600;
	maxHp = 600;
}

Nexus::~Nexus()
{
}

void Nexus::update(float dt)
{
	Object::update(dt);

	for_iter(obj, ((GameScene*)world.currentScene)->objectList)
	{
		if ((*obj)->type == HERO && (*obj)->team == team)
		{
			if (circleCol((*obj)->ColPivotWithPos(), ColPivotWithPos(), 400))
			{
				if ((*obj)->hp < (*obj)->maxHp)
					(*obj)->hp += 1;
				if (((Hero*)(*obj))->mp < ((Hero*)(*obj))->maxMp)
					((Hero*)(*obj))->mp += 1;
			}
		}
	}

	if (hp <= 0)
	{
		GameScene *scene = (GameScene*)world.currentScene;
		scene->isFinished = true;
		if (team == BLACK)
			scene->isKnightWin = true;
		else
			scene->isKnightWin = false;
	}
}

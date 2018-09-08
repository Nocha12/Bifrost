#include "DXUT.h"
#include "Tower.h"
#include "Bullet.h"
#include "World.h"
#include "GameScene.h"
#include "GameManager.h"

Tower::Tower(TeamType team) 
{
	this->team = team;
	this->type = TOWER;
	
	colRange = 45;
	colPivot = Vec2(145, 294);
	attackRange = 300;
	scanRange = 300;

	isAI = true;

	attackFrame = 5;

	if (team == WHITE)
	{
		addChild(animation = new Animation("image/map/knighttower", 10));
		addChild(hpBack = new Sprite("image/UI/hpbar/tower/knightTowerHpbar1.png"));
		addChild(hpBar = new Sprite("image/UI/hpbar/tower/knightTowerHpbar2.png"));
	}
	else if (team == BLACK)
	{
		addChild(animation = new Animation("image/map/eviltower", 10));
		addChild(hpBack = new Sprite("image/UI/hpbar/tower/evilTowerHpbar1.png"));
		addChild(hpBar = new Sprite("image/UI/hpbar/tower/evilTowerHpbar2.png"));
	}

	rect = animation->rect;

	hp = 300;
	maxHp = 300;

	hpBack->pos = Vec2(85, 9);
	hpBar->pos = Vec2(87, 10);
}

Tower::~Tower()
{
}

void Tower::update(float dt)
{
	Object::update(dt);

	GameScene *scene = ((GameScene*)world.currentScene);

	if (hp <= 0)
	{
		hp = 0;
		removeChild(this);
		scene->objectList.remove(this);
		attackTarget = nullptr;
		canBeTarget = false;

		for_iter(iter, scene->objectList)
		{
			if ((*iter)->attackTarget == this)
			{
				(*iter)->attackTarget = nullptr;
			}
		}

		if ((team == WHITE && gameManager.isKnight) || (team == BLACK && !gameManager.isKnight))
		{
			scene->gameUI->brokenTower->visible = true;
			scene->gameUI->die->visible = false;
			scene->gameUI->kill->visible = false;
			scene->gameUI->breakTower->visible = false;
			scene->ChangeTextVisible(scene->gameUI->brokenTower, &scene->textTimer);
		}
		else if ((team == BLACK && gameManager.isKnight) || (team == WHITE && !gameManager.isKnight))
		{
			scene->gameUI->breakTower->visible = true;
			scene->gameUI->die->visible = false;
			scene->gameUI->kill->visible = false;
			scene->gameUI->brokenTower->visible = false;
			scene->ChangeTextVisible(scene->gameUI->breakTower, &scene->textTimer);
		}
	}

	if (attackTarget)
	{
		if (!circleCol(attackTarget->ColPivotWithPos(), ColPivotWithPos(), scanRange))
		{
			attackTarget = nullptr;
			return;
		}
		if ((attackFrame == (int)animation->currentFrame) && !isAttacked)
		{
			Bullet *bullet = new Bullet(attackTarget, 35, true);
			((GameScene*)world.currentScene)->addChild(bullet);
			bullet->setCenter(pos + Vec2(140, 80));
			isAttacked = true;
		}
		else if (!(attackFrame == (int)animation->currentFrame)) {
			isAttacked = false;
		}
	}
}

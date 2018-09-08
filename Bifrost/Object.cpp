#include "DXUT.h"
#include "Object.h"
#include "GameScene.h"
#include "World.h"

Object::Object() : hp(0), maxHp(0), armor(0), attackTarget(nullptr), isAI(false), attackRange(0), scanRange(0), colRange(0), colPivot(0, 0), type(UNKNOWN), isPushed(false), notPush(false), canBeTarget(true), power(0), moveRotation(0), hpBar(nullptr)
{
}

Object::~Object()
{
}

Vec2 Object::ColPivotWithPos()
{
	return pos + colPivot;
}

void Object::update(float dt)
{
	Entity::update(dt);
	
	if (hpBar)
		hpBar->visibleRect.right = hpBar->rect.right * hp / maxHp;

	if (!isPushed && !notPush)
	{
		isPushed = true;
		((GameScene*)world.currentScene)->objectList.push_back(this);
	}

	GameScene *scene = (GameScene*)world.currentScene;

	if (isAI && (!attackTarget || attackTarget->type == NEXUS))
	{
		for_iter(iter, scene->objectList)
		{
			if ((*iter)->type == MINION && circleCol((*iter)->ColPivotWithPos(), ColPivotWithPos(), scanRange) && (*iter)->team != team && canBeTarget)
			{
				attackTarget = *iter;
			}
		}

		if (attackTarget && attackTarget->type != NEXUS)
			return;

		for_iter(iter, scene->objectList)
		{
			if ((*iter)->type == HERO && circleCol((*iter)->ColPivotWithPos(), ColPivotWithPos(), scanRange) && (*iter)->team != team && canBeTarget)
			{
				attackTarget = *iter;
			}
		}

		if (attackTarget && attackTarget->type != NEXUS)
			return;

		for_iter(iter, scene->objectList)
		{
			if ((*iter)->type == TOWER && circleCol((*iter)->ColPivotWithPos(), ColPivotWithPos(), scanRange) && (*iter)->team != team && canBeTarget)
				attackTarget = *iter;
		}

		if ((attackTarget && attackTarget->type != NEXUS) || type == TOWER)
			return;

		for_iter(iter, scene->objectList)
		{
			if ((*iter)->type == NEXUS && (*iter)->team != team)
				attackTarget = *iter;
		}
	}
}

void Object::GetDamage(int damage)
{
	if (armor - damage < 0)
		hp += armor - damage;
	if (hp < 0)
		hp = 0;

	if (team == WHITE)
	{
		Animation *effect;
		
		effect = new Animation("image/evil/effect/baseattack", 3, 10, false, false);

		((GameScene*)world.currentScene)->effectList.push_back(effect);
		((GameScene*)world.currentScene)->addChild(effect);
		if (type == TOWER)
			effect->setCenter(pos + Vec2(140, 268));
		else
			effect->setCenter(center());
	}
	else
	{
		Animation *effect;

		effect = new Animation("image/knight/effect/baseattack", 3, 10, false, false);

		((GameScene*)world.currentScene)->effectList.push_back(effect);
		((GameScene*)world.currentScene)->addChild(effect);
		if (type == TOWER)
			effect->setCenter(pos + Vec2(140, 268));
		else
			effect->setCenter(center());
	}
}
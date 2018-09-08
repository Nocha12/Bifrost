#include "DXUT.h"
#include "Bullet.h"
#include "World.h"
#include "GameScene.h"

Bullet::Bullet(Object *target, int damage, bool isTower) : damage(damage)
{
	attackTarget = target;
	if (target->team == WHITE)
	{
		if (isTower)
			addChild(sprite = new Sprite("image/map/towerattakball/evilattackball.png"));
		else 
			addChild(sprite = new Sprite("image/minion/effect/evilMinion/attackball.png"));
	}
	else if (target->team == BLACK)
	{
		if (isTower)
			addChild(sprite = new Sprite("image/map/towerattakball/knightattackball.png"));
		else
			addChild(sprite = new Sprite("image/minion/effect/knightMinion/attackball.png"));
	}
	rect = sprite->rect;
	sprite->rotationCenter = center();
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt)
{
	Object::update(dt);

	GameScene *scene = (GameScene*)world.currentScene;

	if (attackTarget == nullptr)
	{
		scene->objectList.remove(this);
		removeChild(this);
		return;
	}
	else
	{
		rotation = angle(center(), attackTarget->center());
		pos += Vec2(cosf(rotation), sinf(rotation)) * 350 * dt;

		if (circleCol(center(), attackTarget->center(), 5))
		{
			attackTarget->GetDamage(damage);
			scene->objectList.remove(this);
			removeChild(this);
		}
	}
}



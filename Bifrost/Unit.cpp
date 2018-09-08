#include "DXUT.h"
#include "Unit.h"
#include "GameScene.h"
#include "World.h"
#include "Bullet.h"
#include "GameManager.h"

Unit::Unit() : speed(0), backSpeed(0), isFirstAttack(false), attackFrame(0), attackFrame2(0), isAttacked(false), isLongAttack(false), LEFT(2700), RIGHT(3250)
{
}

Unit::~Unit()
{
}

void Unit::update(float dt)
{
	Object::update(dt);

	GameScene *scene = (GameScene*)world.currentScene;
	
	if (center().y < -center().x + LEFT)
		pos += Vec2(cosf(D3DXToRadian(45)), sinf(D3DXToRadian(45))) * backSpeed * dt;
	else if (center().y > -center().x + RIGHT)
		pos += Vec2(cosf(D3DXToRadian(-135)), sinf(D3DXToRadian(-135))) * backSpeed * dt;

	MuldirAnimation *deadAni = (MuldirAnimation*)animation[DEAD];
	if (hp <= 0 && canBeTarget)
	{
		if (type == HERO && team == WHITE)
		{
			++scene->scoreBlack;
			if (gameManager.isKnight)
			{
				scene->gameUI->brokenTower->visible = false;
				scene->gameUI->die->visible = true; 
				scene->gameUI->kill->visible = false;
				scene->gameUI->breakTower->visible = false;
				scene->ChangeTextVisible(scene->gameUI->die, &scene->textTimer);

				scene->unfollow();
			}
			else
			{
				scene->gameUI->brokenTower->visible = false;
				scene->gameUI->die->visible = false;
				scene->gameUI->kill->visible = true;
				scene->gameUI->breakTower->visible = false;
				scene->ChangeTextVisible(scene->gameUI->kill, &scene->textTimer);
				scene->money += 300;
			}

			animation[STOP]->visible = false;
			animation[SKILLQ]->visible = false;
			animation[SKILLW]->visible = false;
			animation[SKILLE]->visible = false;
			scene->whiteRespawnTimer.reset(5, 1);
			scene->whiteRespawnTimer.onFinished = [](){
				((GameScene*)world.currentScene)->Respawn(WHITE);
			};
		}
		else if (type == HERO && team == BLACK)
		{
			++scene->scoreWhite;
			if (!gameManager.isKnight)
			{
				scene->gameUI->brokenTower->visible = false;
				scene->gameUI->die->visible = true;
				scene->gameUI->kill->visible = false;
				scene->gameUI->breakTower->visible = false;
				scene->ChangeTextVisible(scene->gameUI->die, &scene->textTimer);
				scene->unfollow();
			}
			else
			{
				scene->gameUI->brokenTower->visible = false;
				scene->gameUI->die->visible = false;
				scene->gameUI->kill->visible = true;
				scene->gameUI->breakTower->visible = false;
				scene->ChangeTextVisible(scene->gameUI->kill, &scene->textTimer);
				scene->money += 300;
			}
			animation[STOP]->visible = false;
			animation[SKILLQ]->visible = false;
			animation[SKILLW]->visible = false;
			animation[SKILLE]->visible = false;
			scene->blackRespawnTimer.reset(5, 1);
			scene->blackRespawnTimer.onFinished = [](){
				((GameScene*)world.currentScene)->Respawn(BLACK);
			};
		}
		else 
			scene->money += 20;

		animation[WALK]->visible = false;
		animation[ATTACK]->visible = false;
		animation[DEAD]->visible = true;
		deadAni->Play();
		isAI = false;
		attackTarget = nullptr;
		canBeTarget = false;

		for_iter(iter, scene->objectList)
		{
			if ((*iter)->attackTarget == this)
			{
				(*iter)->attackTarget = nullptr;
			}
		}
	}

	if ((int)deadAni->currentFrame >= deadAni->size)
	{
		removeChild(this);
		scene->objectList.remove(this);
		for_iter(iter, scene->objectList)
		{
			if ((*iter)->attackTarget == this)
			{
				(*iter)->attackTarget = nullptr;
			}
		}
	}

	for_iter(obj, scene->objectList)
	{
		if (*obj == this) continue;

		if (circleCol(ColPivotWithPos(), (*obj)->ColPivotWithPos(), colRange + (*obj)->colRange))
		{
			float t = angle(ColPivotWithPos(), (*obj)->ColPivotWithPos());
			pos -= Vec2(cosf(t), sinf(t)) * backSpeed * dt;
		}
	}

	if (isAI && attackTarget)
	{
		moveRotation = angle(ColPivotWithPos(), attackTarget->ColPivotWithPos());

		MuldirAnimation *attackAni = (MuldirAnimation*)animation[ATTACK];

		if (!circleCol(ColPivotWithPos(), attackTarget->ColPivotWithPos(), attackRange + attackTarget->colRange))
		{
			pos += Vec2(cosf(moveRotation), sinf(moveRotation)) * speed * dt;
			attackAni->visible = false;
			attackAni->Stop();
			attackAni->Reset();
			animation[WALK]->visible = true;
			isFirstAttack = false;
			speed = backSpeed = 150;
			if (!circleCol(attackTarget->ColPivotWithPos(), ColPivotWithPos(), scanRange))
				attackTarget = nullptr;
		}
		else
		{
			if (!isFirstAttack)
			{
				attackAni->Play();
				attackAni->visible = true;
				animation[WALK]->visible = false;
				speed = 0;
				backSpeed = 0;
				isFirstAttack = true;
			}

			if ((attackFrame == (int)attackAni->currentFrame || (attackFrame2 != 0 && attackFrame2 == (int)attackAni->currentFrame)) && !isAttacked)
			{
				isAttacked = true;

				if (isLongAttack && attackTarget)
				{
					Bullet *bullet = new Bullet(attackTarget, 15);
					scene->addChild(bullet);
					bullet->setCenter(pos + Vec2(140, 80));
					isAttacked = true;
				}
				else
				{	 
					attackTarget->GetDamage(power);
				}
			}
			else if (!(attackFrame == (int)attackAni->currentFrame || (attackFrame2 != 0 && attackFrame2 == (int)attackAni->currentFrame))) {
				isAttacked = false;
			}
		}
	}
}
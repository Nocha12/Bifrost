#include "DXUT.h"
#include "Hero.h"
#include "MuldirAnimation.h"
#include "World.h"
#include "GameScene.h"
#include "AfterImage.h"
#include "GameManager.h"
#include "Asset.h"

Hero::Hero() : targetPos(0, 0), skillQColTime(0), skillWColTime(0), skillEColTime(0), skillQTimer(0), skillWTimer(0), skillETimer(0), mp(100), maxMp(100), usingSkill(false), mpBar(nullptr), buff(0)
{
	type = HERO;
	scanRange = 350;
	power = 12;
}

Hero::~Hero()
{
}

bool Hero::UseMp(float use, bool nowUse)
{
	if (mp >= use)
	{
		if (nowUse)
			mp -= use;
		return true;
	}
	
	return false;
}

void Hero::update(float dt)
{
	Unit::update(dt);

	GameScene *scene = (GameScene*)world.currentScene;
	
	if (mpBar)
		mpBar->visibleRect.right = mpBar->rect.right * mp / maxMp;

	if ((gameManager.isKnight && team == WHITE) || (!gameManager.isKnight && team == BLACK))
	{
		scene->gameUI->hp->visibleRect.right = scene->gameUI->hp->rect.right * hp / maxHp;
		scene->gameUI->mp->visibleRect.right = scene->gameUI->mp->rect.right * mp / maxMp;
	
		scene->gameUI->powerText->text = to_string(power);
		scene->gameUI->armorText->text = to_string(armor + 10);
		scene->gameUI->speedText->text = to_string(speed - 350);
	}	

	if (!isAI && canBeTarget)
	{
		if (world.getKeyState('Q') == 1 && skillQTimer >= skillQColTime)
			SkillQ();
		if (world.getKeyState('W') == 1 && skillWTimer >= skillWColTime)
			SkillW();
		if (world.getKeyState('E') == 1 && skillETimer >= skillEColTime)
			SkillE();

		if (skillQTimer < skillQColTime) skillQTimer += dt;
		if (skillWTimer < skillWColTime) skillWTimer += dt;
		if (skillETimer < skillEColTime) skillETimer += dt;

		scene->gameUI->skillQCooltime->visibleRect.bottom = scene->gameUI->skillQCooltime->rect.bottom * (skillQColTime - skillQTimer) / skillQColTime;
		scene->gameUI->skillWCooltime->visibleRect.bottom = scene->gameUI->skillWCooltime->rect.bottom * (skillWColTime - skillWTimer) / skillWColTime;
		scene->gameUI->skillECooltime->visibleRect.bottom = scene->gameUI->skillECooltime->rect.bottom * (skillEColTime - skillETimer) / skillEColTime;


		if (world.getKeyState('1') == 1 && !usingSkill)
		{
			power = 900;
		}

		if (world.getKeyState(VK_RBUTTON) == 2 && !usingSkill)
		{
			MuldirAnimation *attackAni = ((MuldirAnimation*)animation[ATTACK]);
			targetPos = world.getMousePos() - world.currentScene->pos;
			moveRotation = angle(ColPivotWithPos(), targetPos);
			speed = backSpeed;

			animation[WALK]->visible = true;
			attackAni->visible = false;
			attackAni->Stop();

			animation[STOP]->visible = false;
			attackTarget = nullptr;

			for_iter(obj, scene->objectList)
			{
				if (*obj == this || (*obj)->team == team) { continue; }

				if (circleCol(targetPos, (*obj)->ColPivotWithPos(), (*obj)->colRange))
					attackTarget = *obj;
			}
		}

		if (!circleCol(ColPivotWithPos(), targetPos, 5) && !usingSkill) // run
		{
			moveRotation = angle(ColPivotWithPos(), targetPos);
			pos += Vec2(cosf(moveRotation), sinf(moveRotation)) * speed * dt;
		}
		else if (!usingSkill && !isFirstAttack) //SAFE!
		{
			animation[ATTACK]->visible = false;
			animation[WALK]->visible = false;
			animation[STOP]->visible = true;
		}

		if (attackTarget && circleCol(attackTarget->ColPivotWithPos(), ColPivotWithPos(), attackRange + attackTarget->colRange))
		{
			MuldirAnimation *attackAni = ((MuldirAnimation*)animation[ATTACK]);

			if (!isFirstAttack)
			{
				animation[STOP]->visible = false;
				animation[WALK]->visible = false;
				animation[ATTACK]->visible = true;

				speed = 0;
				isFirstAttack = true;
				attackAni->Play();
				targetPos = ColPivotWithPos();
				moveRotation = angle(ColPivotWithPos(), attackTarget->ColPivotWithPos());
			}

			if ((attackFrame == (int)attackAni->currentFrame || (attackFrame2 != 0 && attackFrame2 == (int)attackAni->currentFrame)) && !isAttacked)
			{
				isAttacked = true;
				attackTarget->GetDamage(power);
				asset.sounds[L"sound/baseattack.wav"]->Play();
			}
			else if (!(attackFrame == (int)attackAni->currentFrame || (attackFrame2 != 0 && attackFrame2 == (int)attackAni->currentFrame))) {
				isAttacked = false;
			}
		}
		else
		{
			MuldirAnimation *attackAni = ((MuldirAnimation*)animation[ATTACK]);
			attackAni->Stop();
			attackAni->Reset();
			speed = backSpeed;
			isFirstAttack = false;
		}
	}
}

SkillWPet::SkillWPet()
{
	addChild(animation = new MuldirAnimation(this, "image/knight/skill2/pet", 0));
	colRange = 0; //40
	canBeTarget = false;
}

SkillWPet::~SkillWPet()
{
}

WhiteHero::WhiteHero() : isPetAddChild(false), useSkillE(0), useSkillW(0)
{
	pet = new SkillWPet();
	skillDir = new Sprite("image/knight/effect/skill3.png");
	addChild(skillDir);
	addChild(shieldBack = new Animation("image/knight/effect/sheild/back", 10));
	shieldBack->visible = false;
	addChild(animation[STOP] = new MuldirAnimation(this, "image/knight/stop", 9));
	rect = animation[STOP]->rect;
	addChild(animation[ATTACK] = new MuldirAnimation(this, "image/knight/baseattack", 12));
	animation[ATTACK]->visible = false;
	((MuldirAnimation*)animation[ATTACK])->Stop();
	addChild(animation[DEAD] = new MuldirAnimation(this, "image/knight/dead", 5, 5, false));
	animation[DEAD]->visible = false;
	((MuldirAnimation*)animation[DEAD])->Stop();
	addChild(animation[WALK] = new MuldirAnimation(this, "image/knight/walk", 12));
	animation[WALK]->visible = false;
	addChild(animation[SKILLQ] = new MuldirAnimation(this, "image/knight/skill1", 12, 6, false));
	animation[SKILLQ]->visible = false;
	((MuldirAnimation*)animation[SKILLQ])->Stop();
	addChild(animation[SKILLW] = new MuldirAnimation(this, "image/knight/skill2", 6, 4, false));
	animation[SKILLW]->visible = false;
	((MuldirAnimation*)animation[SKILLW])->Stop();
	addChild(animation[SKILLE] = new MuldirAnimation(this, "image/knight/skill3", 12, 12, false));
	animation[SKILLE]->visible = false;
	((MuldirAnimation*)animation[SKILLE])->Stop();
	addChild(shieldFront = new Animation("image/knight/effect/sheild/front", 10));
	shieldFront->visible = false;
	pos += Vec2(200, 100);
	speed = 400;
	backSpeed = 400;
	team = WHITE;
	skillQColTime = 10;
	skillQTimer = 10;
	skillWColTime = 3;
	skillWTimer = 3;
	skillEColTime = 5;
	skillETimer = 5;
	hp = 300;
	maxHp = 300;
	colPivot = Vec2(175, 220);
	colRange = 30;
	attackRange = 50;
	attackFrame = 4;
	attackFrame2 = 10;

	skillDir->pos = colPivot - Vec2(0, 15);
	skillDir->rotationCenter = Vec2(0, 30);
	skillDir->visible = false;

	addChild(hpBar = new Sprite("image/UI/hpbar/playcharacter/knightHp.png"));
	addChild(mpBar = new Sprite("image/UI/hpbar/playcharacter/knightMp.png"));
	addChild(hpBack = new Sprite("image/UI/hpbar/playcharacter/knight.png"));
	hpBack->pos = Vec2(126, 69);
	hpBar->pos = Vec2(128, 71);
	mpBar->pos = Vec2(128, 79);
}

WhiteHero::~WhiteHero()
{

}

void WhiteHero::update(float dt)
{
	Hero::update(dt);

	GameScene *scene = (GameScene*)world.currentScene;

	if (!isPetAddChild)
	{
		isPetAddChild = true;
		scene->addChild(pet);
		pet->pos = center();
		((MuldirAnimation*)pet->animation)->Invisible();
	}

	skillDir->rotation = angle(ColPivotWithPos(), world.getMousePos() - world.currentScene->pos);
	scene->gameUI->white->setCenter((center() / 20) + Vec2(1127, 565));
	
	if (scene->whiteNexus->rectWithPos().contain(world.getMousePos() - world.currentScene->pos) && !isAI)
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			scene->gameUI->shop->visible = true;
			scene->gameUI->shopBack->visible = true;
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 3; j++)
					scene->gameUI->buyBtn[i][j]->visible = true;
		}
	}

	pet->moveRotation = angle(pet->center(), center());
	if (!circleCol(pet->center(), center(), 50))
	pet->pos -= (-center() + pet->pos) * 0.05f;

	if (useSkillW == 1)
	{
		if (!UseMp(0.1f))
		{
			SkillW();
		}
	}

	if (useSkillE == 1 && world.getKeyState(VK_LBUTTON) == 1 && UseMp(20))
	{
		skillDir->visible = false;
		MuldirAnimation *skillEAnimation = ((MuldirAnimation*)animation[SKILLE]);
		skillETimer = 0;
		animation[SKILLE]->visible = true;
		animation[STOP]->visible = false;
		animation[ATTACK]->visible = false;
		animation[DEAD]->visible = false;
		animation[WALK]->visible = false;
		attackTarget = nullptr;
		usingSkill = true;
		skillEAnimation->Play();

		moveRotation = angle(ColPivotWithPos(), world.getMousePos() - world.currentScene->pos);

		useSkillE = 2;

		afterImageTimer.reset(0.05f, 10);
		afterImageTimer.onTick = [=](){
			AfterImage *img = new AfterImage(skillEAnimation->animation[skillEAnimation->direction]->textures[skillEAnimation->currentFrame]);
			scene->addChild(img);
			img->pos = pos;
		};
	}

	if (useSkillE == 2)
	{
		pos += Vec2(cosf(moveRotation), sinf(moveRotation)) * speed * 2 * dt;
		
		for_iter(obj, scene->objectList)
		{
			if (type == NEXUS || type == TOWER || *obj == this || (*obj)->team == WHITE) continue;

			bool isAttacked = false;
			for_iter(attackedObj, attackedObjList)
			{
				if (*attackedObj == *obj)
					isAttacked = true;
			}
			if (!isAttacked && circleCol(ColPivotWithPos(), (*obj)->ColPivotWithPos(), attackRange + (*obj)->colRange))
			{
				attackedObjList.push_back(*obj);
				(*obj)->GetDamage(power * 2);
			}
		}
	}

	MuldirAnimation *skillQAnimation = (MuldirAnimation*)animation[SKILLQ];

	if (skillQAnimation->currentFrame >= skillQAnimation->size)
	{
		animation[SKILLQ]->visible = false;
		animation[STOP]->visible = true;
		skillQAnimation->Reset();
		skillQAnimation->Stop();
		usingSkill = false;
		targetPos = ColPivotWithPos();
	}

	MuldirAnimation *skillWAnimation = (MuldirAnimation*)animation[SKILLW];

	if (skillWAnimation->currentFrame >= skillWAnimation->size)
	{
		animation[SKILLW]->visible = false;
		animation[STOP]->visible = true;
		skillWAnimation->Reset();
		skillWAnimation->Stop();
		usingSkill = false;
		targetPos = ColPivotWithPos();
	}

	MuldirAnimation *skillEAnimation = (MuldirAnimation*)animation[SKILLE];

	if (skillEAnimation->currentFrame >= skillEAnimation->size)
	{
		animation[SKILLE]->visible = false;
		animation[STOP]->visible = true;
		skillEAnimation->Reset();
		skillEAnimation->Stop();
		usingSkill = false;
		useSkillE = 0;
		targetPos = ColPivotWithPos();
		attackedObjList.clear();
	}
}

void WhiteHero::SkillQ()
{
	if (UseMp(30))
	{
		animation[SKILLQ]->visible = true;
		animation[STOP]->visible = false;
		animation[ATTACK]->visible = false;
		animation[DEAD]->visible = false;
		animation[WALK]->visible = false;
		usingSkill = true;
		attackTarget = nullptr;
		targetPos = ColPivotWithPos();
		((MuldirAnimation*)animation[SKILLQ])->Play();
		shieldTimer.reset(5, 1);
		shieldFront->visible = true;
		shieldBack->visible = true;
		armor += 5;
		shieldTimer.onFinished = [=](){
			armor -= 5;
			shieldFront->visible = false;
			shieldBack->visible = false;
		};
		skillQTimer = 0;
	}
}

void WhiteHero::SkillW()
{
	if (useSkillW == 0 && UseMp(0.01f))
	{
		asset.sounds[L"sound/nightskill2.wav"]->Play();
		animation[SKILLW]->visible = true;
		animation[STOP]->visible = false;
		animation[ATTACK]->visible = false;
		animation[DEAD]->visible = false;
		animation[WALK]->visible = false;
		attackTarget = nullptr;
		usingSkill = true;
		targetPos = ColPivotWithPos();
		((MuldirAnimation*)animation[SKILLW])->Play();

		((MuldirAnimation*)pet->animation)->FaidIn();
		useSkillW = 1;
		power += 30;
	}
	else if (useSkillW == 1)
	{
		asset.sounds[L"sound/nightskill2.wav"]->Play();
		((MuldirAnimation*)pet->animation)->FaidOut();
		useSkillW = 0;
		power -= 30;
	}
	skillWTimer = 0;
}

void WhiteHero::SkillE()
{
	if (useSkillE == 0 && UseMp(20, false))
	{
		skillDir->visible = true;
		useSkillE = 1;
	}
	else
	{
		skillDir->visible = false;
		useSkillE = 0;
	}
}

//----------------------------------------------------------------------

SkillWCircle::SkillWCircle()
{
	notPush = true;
	GameScene *scene = (GameScene*)world.currentScene;

	addChild(animation = new MuldirAnimation(this, "image/evil/effect/skill2", 10));
	rect = animation->rect;
	colRange = 0; //40
	colPivot = center() + Vec2(0, 10);
	canBeTarget = false;

	damageTimer.reset(0.1f, 30);
	damageTimer.onTick = [=](){
		for_iter(iter, scene->objectList)
		{
			if (circleCol(ColPivotWithPos(), (*iter)->ColPivotWithPos(), 40 + (*iter)->colRange))
			{
				if ((*iter)->team == WHITE && (*iter)->type != TOWER && (*iter)->type != NEXUS)
					(*iter)->GetDamage(5);
			}
		}
	};

	deleteTimer.reset(3, 1);
	deleteTimer.onFinished = [=](){
		removeChild(this);
	};
}

SkillWCircle::~SkillWCircle(){}

BlackHero::BlackHero() : useSkillE(0), useSkillW(0), isCircleAddChild(false), isShaked(false)
{
	colPivot = Vec2(211, 255);
	skillWCircle = new Sprite("image/evil/effect/skill2.png");
	skillWCircle->visible = false;
	addChild(skillECircle = new Sprite("image/evil/effect/skill3Doing.png"));
	skillECircle->setCenter(colPivot);
	skillECircle->visible = false;

	addChild(animation[STOP] = new MuldirAnimation(this, "image/evil/stop", 8));
	rect = animation[STOP]->rect;
	addChild(animation[ATTACK] = new MuldirAnimation(this, "image/evil/baseattack", 9));
	animation[ATTACK]->visible = false;
	((MuldirAnimation*)animation[ATTACK])->Stop();
	addChild(animation[DEAD] = new MuldirAnimation(this, "image/evil/dead", 9, 9, false));
	animation[DEAD]->visible = false;
	((MuldirAnimation*)animation[DEAD])->Stop();
	addChild(animation[WALK] = new MuldirAnimation(this, "image/evil/walk", 17));
	animation[WALK]->visible = false;
	addChild(animation[SKILLQ] = new MuldirAnimation(this, "image/evil/skill1", 11, 8, false));
	animation[SKILLQ]->visible = false;
	((MuldirAnimation*)animation[SKILLQ])->Stop();
	addChild(animation[SKILLW] = new MuldirAnimation(this, "image/evil/skill2", 12, 10, false));
	animation[SKILLW]->visible = false;
	((MuldirAnimation*)animation[SKILLW])->Stop();
	addChild(animation[SKILLE] = new MuldirAnimation(this, "image/evil/skill3", 23, 8, false));
	animation[SKILLE]->visible = false;
	((MuldirAnimation*)animation[SKILLE])->Stop();
	pos += Vec2(200, 100);
	speed = 400;
	backSpeed = 400;
	team = BLACK;
	skillQColTime = 5;
	skillQTimer = 5;
	skillWColTime = 10;
	skillWTimer = 10;
	skillEColTime = 20;
	skillETimer = 20;
	hp = 300;
	maxHp = 300;
	colRange = 35;
	attackRange = 120;
	attackFrame = 7;
	power = 20;

	addChild(hpBar = new Sprite("image/UI/hpbar/playcharacter/evilHp.png"));
	addChild(mpBar = new Sprite("image/UI/hpbar/playcharacter/evilMp.png"));
	addChild(hpBack = new Sprite("image/UI/hpbar/playcharacter/evil.png"));
	hpBack->pos = Vec2(159, 94);
	hpBar->pos = Vec2(160, 95);
	mpBar->pos = Vec2(160, 103);
}

BlackHero::~BlackHero()
{

}

void BlackHero::update(float dt)
{
	Hero::update(dt);

	GameScene *scene = (GameScene*)world.currentScene;

	if (!isCircleAddChild)
	{
		scene->addChild(skillWCircle);
		isCircleAddChild = true;
	}
	skillWCircle->setCenter(world.getMousePos() - world.currentScene->pos);

	scene->gameUI->black->setCenter((center() / 20) + Vec2(1127, 565));

	if (scene->blackNexus->rectWithPos().contain(world.getMousePos() - world.currentScene->pos) && !isAI)
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			scene->gameUI->shop->visible = true;
			scene->gameUI->shopBack->visible = true;
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 3; j++)
					scene->gameUI->buyBtn[i][j]->visible = true;
		}
	}

	if (useSkillW == 1 && world.getKeyState(VK_LBUTTON) == 1 && UseMp(25))
	{
		skillWTimer = 0;
		skillWCircle->visible = false;
		MuldirAnimation *skillWAnimation = ((MuldirAnimation*)animation[SKILLW]);
		SkillWCircle *circle = new SkillWCircle();
		scene->addChild(circle);
		circle->pos = (world.getMousePos() - world.currentScene->pos);
		circle->pos -= circle->rect.center();

		animation[SKILLW]->visible = true;
		animation[STOP]->visible = false;
		animation[ATTACK]->visible = false;
		((MuldirAnimation*)animation[ATTACK])->Stop();
		animation[DEAD]->visible = false;
		animation[WALK]->visible = false;
		attackTarget = nullptr;
		usingSkill = true;
		skillWAnimation->Play();

		moveRotation = angle(ColPivotWithPos(), world.getMousePos() - world.currentScene->pos);
		circle->moveRotation = angle(circle->center(), center());

		useSkillW = 2;
	}

	if (useSkillE == 1 && world.getKeyState(VK_LBUTTON) == 1)
	{
		for_iter(obj, scene->objectList)
		{
			if (*obj == this || (*obj)->team == team || (*obj)->type != MINION) { continue; }

			if (circleCol(world.getMousePos() - world.currentScene->pos, (*obj)->ColPivotWithPos(), (*obj)->colRange) && UseMp(35))
			{
				skillETimer = 0;
				skillECircle->visible = false;
				(*obj)->team = BLACK;
				MuldirAnimation *skillEAnimation = ((MuldirAnimation*)animation[SKILLE]);

				animation[SKILLE]->visible = true;
				animation[STOP]->visible = false;
				animation[ATTACK]->visible = false;
				((MuldirAnimation*)animation[ATTACK])->Stop();
				animation[DEAD]->visible = false;
				animation[WALK]->visible = false;
				attackTarget = nullptr;
				usingSkill = true;
				skillEAnimation->Play();

				moveRotation = angle(ColPivotWithPos(), world.getMousePos() - world.currentScene->pos);
				(*obj)->attackTarget = nullptr;
				(*obj)->mindControl->visible = true;

				for_iter(iter, scene->objectList)
				{
					if ((*iter)->attackTarget == this)
					{
						(*iter)->attackTarget = nullptr;
					}
				}
			}
		}

		useSkillE = 2;
	}

	MuldirAnimation *skillQAnimation = (MuldirAnimation*)animation[SKILLQ];

	if ((int)skillQAnimation->currentFrame == 6 && !isShaked)
	{
		isShaked = true;
		if (attackTarget)
			attackTarget->GetDamage(power * 2);
		scene->shake(5, 10, 0.05f);
	}
	else if ((int)skillQAnimation->currentFrame != 6)
		isShaked = false;

	if (skillQAnimation->currentFrame >= skillQAnimation->size)
	{
		animation[SKILLQ]->visible = false;
		animation[ATTACK]->visible = true;
		((MuldirAnimation*)animation[ATTACK])->Reset();
		((MuldirAnimation*)animation[ATTACK])->Play();
		skillQAnimation->Reset();
		skillQAnimation->Stop();
		usingSkill = false;
		targetPos = ColPivotWithPos();

	}

	if (skillQAnimation->currentFrame >= skillQAnimation->size)
	{
		animation[SKILLQ]->visible = false;
		animation[ATTACK]->visible = true;
		((MuldirAnimation*)animation[ATTACK])->Reset();
		((MuldirAnimation*)animation[ATTACK])->Play();
		skillQAnimation->Reset();
		skillQAnimation->Stop();
		usingSkill = false;
		targetPos = ColPivotWithPos();
		
	}

	MuldirAnimation *skillWAnimation = (MuldirAnimation*)animation[SKILLW];

	if (skillWAnimation->currentFrame >= skillWAnimation->size)
	{
		animation[SKILLW]->visible = false;
		animation[STOP]->visible = true;
		skillWAnimation->Reset();
		skillWAnimation->Stop();
		usingSkill = false;
		targetPos = ColPivotWithPos();
		useSkillW = 0;
	}

	MuldirAnimation *skillEAnimation = (MuldirAnimation*)animation[SKILLE];

	if (skillEAnimation->currentFrame >= skillEAnimation->size)
	{
		animation[SKILLE]->visible = false;
		animation[STOP]->visible = true;
		skillEAnimation->Reset();
		skillEAnimation->Stop();
		usingSkill = false;
		useSkillE = 0;
		targetPos = ColPivotWithPos();
	}
}

void BlackHero::SkillQ()
{
	if (attackTarget && UseMp(10))
	{
		skillQTimer = 0;
		animation[SKILLQ]->visible = true;
		animation[STOP]->visible = false;
		((MuldirAnimation*)animation[ATTACK])->Stop();
		animation[ATTACK]->visible = false;
		animation[WALK]->visible = false;
		usingSkill = true;
		targetPos = ColPivotWithPos();
		((MuldirAnimation*)animation[SKILLQ])->Play();
	}
}

void BlackHero::SkillW()
{
	if (useSkillW == 0 && UseMp(25, false))
	{
		skillWCircle->visible = true;
		useSkillW = 1;
	}
	else
	{
		skillWCircle->visible = false;
		useSkillW = 0;
	}
}

void BlackHero::SkillE()
{
	if (useSkillE == 0 && UseMp(35, false))
	{
		skillECircle->visible = true;
		useSkillE = 1;
	}
	else
	{
		skillECircle->visible = false;
		useSkillE = 0;
	}
}
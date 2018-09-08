#pragma once
#include "Unit.h"
#include "Timer.h"

class Hero :
	public Unit
{
public:
	Hero();
	~Hero();

	Vec2 targetPos;

	void update(float dt);

	virtual void SkillQ() = 0;
	virtual void SkillW() = 0;
	virtual void SkillE() = 0;

	bool UseMp(float use, bool nowUse = true);

	float mp;
	int maxMp;

	float skillQTimer;
	float skillWTimer;
	float skillETimer;
	float skillQColTime;
	float skillWColTime;
	float skillEColTime;

	int buff;

	bool usingSkill;	

	Sprite *mpBar;
};

class SkillWPet : public Object
{
public:
	SkillWPet();
	~SkillWPet();

	Entity *animation;
};

class WhiteHero : public Hero
{
public:
	WhiteHero();
	~WhiteHero();

	SkillWPet *pet;

	Animation *shieldFront;
	Animation *shieldBack;
	Sprite *skillDir;

	Timer shieldTimer;
	Timer afterImageTimer;

	void SkillQ();
	void SkillW();
	void SkillE();
	void update(float dt);

	bool isPetAddChild;
	int useSkillW;
	int useSkillE;

	list<Object*> attackedObjList;
};

class SkillWCircle : public Object
{
public:
	SkillWCircle();
	~SkillWCircle();

	Entity *animation;

	Timer damageTimer;
	Timer deleteTimer;
};

class BlackHero : public Hero
{
public:
	BlackHero();
	~BlackHero();

	void SkillQ();
	void SkillW();
	void SkillE();
	
	int useSkillW;
	int useSkillE;

	Sprite *skillWCircle;
	Sprite *skillECircle;

	bool isCircleAddChild;
	bool isShaked;

	void update(float dt);
};



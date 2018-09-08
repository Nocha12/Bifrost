#pragma once
#include "Entity.h"
#include "Sprite.h"

class Object : public Entity
{
public:
	Object();
	~Object();

	void update(float dt);

	void GetDamage(int damage);
	Vec2 ColPivotWithPos();

	enum ObjectType
	{
		NEXUS,
		TOWER,
		MINION,
		HERO,
		BULLET,
		UNKNOWN
	};

	enum TeamType
	{
		WHITE,
		BLACK
	};

	ObjectType type;
	TeamType team;

	int hp;
	int maxHp;
	int armor;

	Object *attackTarget;
	bool isAI;
	float moveRotation;
	float attackRange;
	float scanRange;
	float colRange;
	Vec2 colPivot;
	int attackFrame, attackFrame2;
	bool isFirstAttack;
	bool isAttacked;
	bool isPushed;
	bool notPush;
	bool canBeTarget;
	int power;

	Sprite *mindControl;

	Sprite *hpBar;
	Sprite *hpBack;
};


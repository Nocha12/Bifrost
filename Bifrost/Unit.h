#pragma once
#include "Object.h"
#include "MuldirAnimation.h"

class Unit :
	public Object
{
public:
	Unit();
	~Unit();

	enum AnimationType {
		STOP,
		ATTACK,
		DEAD,
		WALK,
		SKILLQ,
		SKILLW,
		SKILLE
	};

	int speed;
	int backSpeed;
	int attackFrame, attackFrame2;
	bool isFirstAttack;
	bool isAttacked;
	bool isLongAttack;
	const int LEFT;
	const int RIGHT;

	void update(float dt);

	map<AnimationType, Entity*> animation;
};


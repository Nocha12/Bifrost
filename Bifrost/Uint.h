#pragma once
#include "Object.h"
#include "MuldirAnimation.h"

class Uint :
	public Object
{
public:
	Uint();
	~Uint();

	enum AnimationType {
		STOP,
		ATTACK,
		DEAD,
		WALK,
		SKILLQ,
		SKILLW,
		SKILLE
	};

	map<AnimationType, Entity*> animation;
};


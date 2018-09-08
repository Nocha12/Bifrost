#pragma once
#include "Object.h"
#include "Animation.h"

class Bullet : public Object
{
public:
	Bullet(Object *target, int damage, bool isTower = false);
	~Bullet();
	
	int damage;
	Sprite *sprite;

	void update(float dt);
};


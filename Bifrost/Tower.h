#pragma once
#include "Object.h"
#include "Animation.h"

class Tower : public Object
{
public:
	Tower(TeamType team);
	~Tower();

	void update(float dt);
	
	Animation *animation;
};


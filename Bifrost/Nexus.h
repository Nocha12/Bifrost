#pragma once
#include "Object.h"
#include "Animation.h"
class Nexus :
	public Object
{
public:
	Nexus(TeamType type);
	~Nexus();
	Animation *animation;

	void update(float dt);
};


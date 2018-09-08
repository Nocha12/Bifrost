#pragma once
#include "Unit.h"
#include "Sprite.h"

class Minion : public Unit
{
public:
	Minion(TeamType team);
	~Minion();
};

class SpecialMinion : public Unit
{
public:
	SpecialMinion(TeamType team);
	~SpecialMinion();
};


#pragma once
#include "Define.h"

class Timer
{
public:
	Timer();
	~Timer();

	void update(float dt);
	void reset(float duration, int count);

	function<void()> onTick;
	function<void()> onFinished;

	pair<int, int> count; 
	pair<float, float> duration;
	bool active;
};


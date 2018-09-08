#include "DXUT.h"
#include "Timer.h"
#include "World.h"

Timer::Timer() : active(false), count(0, 0), duration(0, 0)
{
	onTick = [](){};
	onFinished = [](){};

	world.timers.push_back(this);
}

Timer::~Timer()
{
	world.timers.remove(this);
}

void Timer::reset(float duration, int count)
{
	this->duration.first = 0;
	this->duration.second = duration;
	this->count.first = 0;
	this->count.second = count;
	active = true;
}

void Timer::update(float dt)
{
	if (!active) return;

	duration.first += dt;

	if (duration.first > duration.second)
	{
		//if ((!onTick && !onFinished) || count.second == 0 || duration.second == 0){
		//	return;
		//}
		onTick();
		duration.first = 0;

		if (++count.first == count.second)
		{
			onFinished();
			active = false;
			return;
		}
	}
}
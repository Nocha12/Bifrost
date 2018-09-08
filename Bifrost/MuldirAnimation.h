#pragma once
#include "Animation.h"
#include "Entity.h"
#include "Timer.h"

class MuldirAnimation : public Entity
{
public:
	MuldirAnimation(Entity *target, string p, int fileNum, float fps = 8, bool isLoop = true, bool isDDS = true); 
	~MuldirAnimation();

	void Stop();
	void Play();
	void Reset();
	void Invisible();
	void FaidIn();
	void FaidOut();

	void update(float dt);
	void render();

	Animation *animation[8];
	Entity *target;
	int direction;
	int size;

	float faid;
	Timer faidTimer;

	float currentFrame;
};


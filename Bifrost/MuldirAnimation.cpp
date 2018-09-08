#include "DXUT.h"
#include "MuldirAnimation.h"
#include "Unit.h"

MuldirAnimation::MuldirAnimation(Entity *target, string p, int fileNum, float fps, bool isLoop, bool isDDS) : currentFrame(0), target(target)
{
	for (int i = 0; i < 8; ++i)
	{
		animation[i] = new Animation(p + "/" + to_string(i), fileNum, fps, isLoop, isDDS);
		addChild(animation[i]);
	}

	rect = animation[0]->rect;
	direction = 0;
	size = animation[0]->textures.size() - 1;
}

MuldirAnimation::~MuldirAnimation()
{
}

void MuldirAnimation::update(float dt)
{
	Entity::update(dt);
	int angle = (int)D3DXToDegree(((Unit*)target)->moveRotation) - 180 - 22;

	if (angle < 0) angle += 360;
	direction = angle / 45;
	animation[direction]->update(dt);
	animation[direction]->visible = true;
	currentFrame = animation[direction]->currentFrame;
	for (int i = 0; i < 8; ++i)
		if (i != direction)
			animation[i]->visible = false;
}

void MuldirAnimation::render()
{
	Entity::render();
	
	if (visible)
		animation[direction]->render();
}

void MuldirAnimation::Stop()
{
	for (int i = 0; i < 8; ++i)
		animation[i]->stop = true;
}

void MuldirAnimation::Play()
{
	for (int i = 0; i < 8; ++i)
		animation[i]->stop = false;
}

void MuldirAnimation::Reset()
{
	for (int i = 0; i < 8; ++i)
		animation[i]->currentFrame = 0;
}

void MuldirAnimation::Invisible()
{
	for (int i = 0; i < 8; ++i)
		animation[i]->color.a = 0;
}

void MuldirAnimation::FaidIn()
{
	faid = 0;
	faidTimer.reset(0.1f, 100);
	faidTimer.onTick = [=](){
		for (int i = 0; i < 8; ++i)
			animation[i]->color.a = faid += 0.01f;
	};
}

void MuldirAnimation::FaidOut()
{
	faid = 1;
	faidTimer.reset(0.1f, 100);
	faidTimer.onTick = [=](){
		for (int i = 0; i < 8; ++i)
			animation[i]->color.a = faid -= 0.01f;
	};
}
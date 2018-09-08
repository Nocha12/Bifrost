#pragma once
#include "Entity.h"
#include "Timer.h"
class Scene :
	public Entity
{
public:
	Scene();
	~Scene();

	void follow(Entity *target, Vec2 offset = Vec2(1280 / 2, 720 / 2));
	void unfollow();

	void update(float dt);
	void shake(int n, float range, float duration);

	Timer shakeTimer;
	Entity *followTarget;
	Vec2 followOffset;
};


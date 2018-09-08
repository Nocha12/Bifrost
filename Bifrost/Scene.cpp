#include "DXUT.h"
#include "Scene.h"

Scene::Scene() : followTarget(nullptr)
{
}

Scene::~Scene()
{
}

void Scene::follow(Entity *target, Vec2 offset)
{
	followTarget = target;
	followOffset = offset;
}

void Scene::unfollow()
{
	followTarget = nullptr;
}

void Scene::shake(int n, float range, float duration)
{
	shakeTimer.reset(duration, n);
	shakeTimer.onTick = [=]()
	{
		pos = pos + Vec2(random(-range, range), random(-range, range));
	};
}

void Scene::update(float dt)
{
	Entity::update(dt);
	if (followTarget)
	{
		pos += (-followTarget->center() + followOffset - pos) * 0.15f;
	}
}


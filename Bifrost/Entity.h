#pragma once
#include "Define.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update(float dt);
	virtual void render();

	void addChild(Entity *child);
	void removeChild(Entity *child);
	void setCenter(Vec2 pos);
	Vec2 center();
	Rect rectWithPos();

	list<Entity*> children;
	Entity *parent;
	Rect rect;
	Rect visibleRect;
	Vec2 pos;
	float rotation;
	Vec2 rotationCenter;
	Vec2 scale;
	Vec2 scaleCenter;
	D3DXMATRIX matrix;
	bool visible;
	bool removing;
};


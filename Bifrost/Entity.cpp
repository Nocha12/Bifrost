#include "DXUT.h"
#include "Entity.h"

Entity::Entity()
	: parent(nullptr),
	rect(0, 0, 0, 0),
	visibleRect(0, 0, 0, 0),
	pos(0, 0),
	rotation(0),
	rotationCenter(0, 0),
	scale(1, 1),
	scaleCenter(0, 0),
	visible(true),
	removing(false)
{
}

Entity::~Entity()
{
	for_iter(iter, children)
		SAFE_DELETE(*iter);
}

void Entity::update(float dt)
{
	for_iter(iter, children)
		(*iter)->update(dt);
	
	for_iter(iter, children)
	{
		if (!(*iter)->removing) continue;

		SAFE_DELETE(*iter);
		iter = children.erase(iter);
		if (iter == children.end())
			break;
	}
}

void Entity::render()
{
	if (!visible) return;

	D3DXMatrixTransformation2D(&matrix, &scaleCenter, 0, &scale, &rotationCenter, rotation, &pos);

	if (parent)
		matrix *= parent->matrix;
	for_iter(iter, children)
		(*iter)->render();
}

void Entity::addChild(Entity *child)
{
	children.push_back(child);
	child->parent = this;
}

void Entity::removeChild(Entity *child)
{
	child->removing = true;
}

Vec2 Entity::center()
{
	return pos + rect.center();
}

void Entity::setCenter(Vec2 pos)
{
	this->pos = pos;
	this->pos -= rect.center();
}

Rect Entity::rectWithPos()
{
	return rect.offset(pos);
}
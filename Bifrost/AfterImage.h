#pragma once
#include "Entity.h"
#include "Sprite.h"
class AfterImage :
	public Entity
{
public:
	AfterImage(Texture *texture);
	~AfterImage();

	void update(float dt);

	Sprite *sprite;
};
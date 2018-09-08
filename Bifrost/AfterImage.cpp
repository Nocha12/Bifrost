#include "DXUT.h"
#include "AfterImage.h"

AfterImage::AfterImage(Texture *texture)
{
	addChild(sprite = new Sprite());
	sprite->setTexture(texture);
	sprite->color.a = 0.7f;
}

AfterImage::~AfterImage()
{
}

void AfterImage::update(float dt)
{
	Entity::update(dt);

	if (sprite->color.a <= 0)
		removeChild(this);
	
	sprite->color.a -= 0.01f;
}
#include "DXUT.h"
#include "Sprite.h"
#include "Asset.h"
#include "World.h"

Sprite::Sprite() : color(1, 1, 1, 1)
{
	texture = nullptr;
}

Sprite::Sprite(path p) : color(1, 1, 1, 1)
{
	setPath(p);
}

Sprite::~Sprite()
{
}

void Sprite::setPath(path p)
{
	texture = asset.getTexture(p);
	visibleRect = rect = Rect(0, texture->info.Width, 0, texture->info.Height);
}

void Sprite::setTexture(Texture *t)
{
	texture = t;
	visibleRect = rect = Rect(0, texture->info.Width, 0, texture->info.Height);
}

void Sprite::render()
{
	if (!visible || texture == nullptr) return;
	Entity::render();

	world.rootSprite->Begin(D3DXSPRITE_ALPHABLEND);
	world.rootSprite->SetTransform(&matrix);
	world.rootSprite->Draw(texture->d3dSprite, &visibleRect, NULL, NULL, color);
	world.rootSprite->End();
}
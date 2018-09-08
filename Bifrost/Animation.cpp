#include "DXUT.h"
#include "Animation.h"
#include "Asset.h"

Animation::Animation(string p, int fileNum, float fps, bool isLoop, bool isDDS) : fps(fps), isLoop(isLoop), currentFrame(0), stop(false)
{
	if (isDDS)
		for (int i = 0; i <= fileNum; ++i)
			textures.push_back(asset.getTexture(p + "/" + to_string(i) + ".dds"));
	else 
		for (int i = 0; i <= fileNum; ++i)
			textures.push_back(asset.getTexture(p + "/" + to_string(i) + ".png"));

	texture = textures[0];

	visibleRect = rect = Rect(0, texture->info.Width, 0, texture->info.Height);
}

Animation::~Animation()
{
}

void Animation::update(float dt)
{
	Entity::update(dt);

	if (stop) return;

	currentFrame += fps * dt;

	if (currentFrame >= textures.size())
	{
		if (isLoop)
			currentFrame = 0;
		else
			currentFrame = textures.size() - 1;
	}

	texture = textures[int(currentFrame)];
}
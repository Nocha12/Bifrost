#pragma once
#include "Texture.h"
#include "Sprite.h"

class Animation : public Sprite
{
public:
	Animation(string p, int fileNum, float fps = 8, bool isLoop = true, bool isDDS = true);
	~Animation();

	void update(float dt);

	float currentFrame;
	float fps;
	bool isLoop;
	bool stop;
	vector<Texture*> textures;
};


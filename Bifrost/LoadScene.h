#pragma once
#include "Scene.h"
#include "Animation.h"
#include "Sprite.h"

class LoadScene :
	public Scene
{
public:
	LoadScene();
	~LoadScene();

	Sprite *barBack;
	Sprite *bar;
	Animation *loading;

	void update(float dt);
};


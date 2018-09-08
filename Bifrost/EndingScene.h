#pragma once
#include "Scene.h"
#include "Animation.h"

class EndingScene :
	public Scene
{
public:
	EndingScene(bool isKnightWin);
	~EndingScene();

	void update(float dt);

	Animation *ed;
};


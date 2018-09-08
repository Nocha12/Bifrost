#pragma once
#include "Scene.h"
#include "Animation.h"
#include "Sprite.h"

class MainScene :
	public Scene
{
public:
	MainScene();
	~MainScene();

	Sprite *gameStart;
	Sprite *howToPlay;
	Sprite *introduce;
	Sprite *exitB;

	Sprite *howToPlay1;
	Sprite *howToPlay2;
	Sprite *intro1;

	Sprite *charSelectBack;
	Sprite *devilSelect;
	Sprite *knightSelect;

	Animation *op;
	void update(float dt);
};


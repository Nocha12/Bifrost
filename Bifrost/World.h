#pragma once
#include "Define.h"
#include "Scene.h"
#include "Timer.h"

class World
{
public:
	World();
	~World();

	void init();
	void dispose();
	void update(float dt);
	void render();
	void changeScene(Scene *scene);
	int getKeyState(int vk);
	Vec2 getMousePos();

	bool lastKeys[256];
	bool currentKeys[256];
	Scene *currentScene;
	POINT mousePoint;
	LPD3DXSPRITE rootSprite;
	list<Timer*> timers;
};

extern World world;


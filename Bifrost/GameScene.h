#pragma once
#include "Scene.h"
#include "Object.h"
#include "Sprite.h"
#include "Timer.h"
#include "UI.h"
#include"Hero.h"
#include "Nexus.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void update(float dt);
	void render();

	void init();

	bool BuyItem(int useMoney);

	void Respawn(Object::TeamType type);

	void ChangeTextVisible(Sprite *sprite, Timer *timer)
	{
		timer->reset(5, 1);
		timer->onFinished = [=]()
		{
			sprite->visible = false;
		};
	}

	Nexus *whiteNexus;
	Nexus *blackNexus;

	WhiteHero *whiteHero;
	BlackHero *blackHero;

	list<Object*> objectList;
	list<Animation*> effectList;
	Sprite *back;
	Sprite *backLight;
	
	Vec2 whiteMinionSpawnPos;
	Vec2 blackMinionSpawnPos;

	Timer minionSpawnTimer;
	Timer minionCrownSpawnTimer;
	Timer whiteRespawnTimer;
	Timer blackRespawnTimer;;

	Timer textTimer;

	bool isFinished;
	bool isKnightWin;

	bool isBackFaidIn;
	bool isLightFaidIn;

	int money;
	int scoreWhite;
	int scoreBlack;
	float sec;
	int minit;

	float faid;

	UI *gameUI;
};


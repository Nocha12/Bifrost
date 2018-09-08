#include "DXUT.h"
#include "GameScene.h"
#include "Sprite.h"
#include "Animation.h"
#include "Hero.h"
#include "Nexus.h"
#include "Minion.h"
#include "Tower.h"
#include "GameManager.h"
#include "World.h"
#include "EndingScene.h"
#include "Asset.h"

GameScene::GameScene() : whiteMinionSpawnPos(512, 2400), blackMinionSpawnPos(2312, 429), money(0), isFinished(false), isKnightWin(false), scoreWhite(0), scoreBlack(0), sec(0), minit(0)
{
	gameUI = new UI();

	init();

	minionSpawnTimer.reset(20, INT_MAX);
	minionCrownSpawnTimer.reset(2, 3);
	
	minionSpawnTimer.onTick = [=](){
		minionCrownSpawnTimer.reset(2, 3);
	};
	minionCrownSpawnTimer.onTick = [=](){
		Minion *whiteMinion = new Minion(Object::WHITE);
		whiteMinion->pos = whiteMinionSpawnPos;
		addChild(whiteMinion);
		Minion *blackMinion = new Minion(Object::BLACK);
		blackMinion->pos = blackMinionSpawnPos;
		addChild(blackMinion);
	};
	minionCrownSpawnTimer.onFinished = [=](){
		SpecialMinion *whiteMinion = new SpecialMinion(Object::WHITE);
		whiteMinion->pos = whiteMinionSpawnPos;
		addChild(whiteMinion);
		SpecialMinion *blackMinion = new SpecialMinion(Object::BLACK);
		blackMinion->pos = blackMinionSpawnPos;
		addChild(blackMinion);
	};

	asset.sounds[L"sound/ingameBGM.wav"]->Play();
}

GameScene::~GameScene()
{
	SAFE_DELETE(gameUI);
}

void GameScene::update(float dt)
{
	Scene::update(dt);

	if (!asset.sounds[L"sound/ingameBGM.wav"]->IsSoundPlaying())
		asset.sounds[L"sound/ingameBGM.wav"]->Play();

	if (isBackFaidIn && back->color.a <= 1)
		back->color.a += 0.01f;
	else if (back->color.a >= 1)
		isBackFaidIn = false;
	if (!isBackFaidIn && back->color.a >= 0)
		back->color.a -= 0.01f;
	else if (back->color.a <= 0)
		isBackFaidIn = true;

	if (isLightFaidIn && backLight->color.a <= 1)
		backLight->color.a += 0.01f;
	else if (backLight->color.a >= 1)
		isLightFaidIn = false;
	if (!isLightFaidIn && backLight->color.a >= 0.3f)
		backLight->color.a -= 0.01f;
	else if (backLight->color.a <= 0.3f)
		isLightFaidIn = true;

	if (pos.x > 0)
		pos.x = 0;
	if (pos.x < -3000 + followOffset.x * 2)
		pos.x = -3000 + followOffset.x * 2;
	if (pos.y > 0)
		pos.y = 0;
	if (pos.y < -3000 + followOffset.y * 2)
		pos.y = -3000 + followOffset.y * 2;

	sec += dt;
	if (sec >= 60)
	{
		sec -= 60;
		++minit;
	}
	gameUI->timeText->text = "";
	if (minit <= 10)
		gameUI->timeText->text += ("0" + to_string(minit));
	else
		gameUI->timeText->text += minit;
	gameUI->timeText->text += ":";
	if (sec <= 10)
		gameUI->timeText->text += ("0" + to_string((int)sec));
	else
		gameUI->timeText->text += to_string((int)sec);

	gameUI->moneyText->text = to_string(money);
	gameUI->whiteScoreText->text = to_string(scoreWhite);
	gameUI->blackScoreText->text = to_string(scoreBlack);

	if (isFinished)
	{
		asset.sounds[L"sound/ingameBGM.wav"]->Stop();
		world.changeScene(new EndingScene(isKnightWin));
		return;
	}

	gameUI->moneyText->text = to_string(money);
	gameUI->whiteScoreText->text = to_string(scoreWhite);
	gameUI->blackScoreText->text = to_string(scoreBlack);

	if (gameUI->shop->visible)
	{
		if (!gameUI->shop->rectWithPos().contain(world.getMousePos()))
		{
			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				gameUI->shop->visible = false;
				gameUI->shopBack->visible = false;
				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						gameUI->buyBtn[i][j]->visible = false;
					}
				}
			}
		}
		else if (gameUI->buyBtn[0][0]->rectWithPos().contain(world.getMousePos()) && !gameUI->itemList[0]->visible)
		{
			if (world.getKeyState(VK_LBUTTON) == 1 && BuyItem(300))
			{
				asset.sounds[L"sound/shopbuybutton.wav"]->Play();
				gameUI->itemList[0]->visible = true;

				if (gameManager.isKnight)
					whiteHero->hp = whiteHero->maxHp += 50;
				else
					blackHero->hp = blackHero->maxHp += 50;
			}
		}
		else if (gameUI->buyBtn[0][1]->rectWithPos().contain(world.getMousePos()) && !gameUI->itemList[1]->visible)
		{
			if (world.getKeyState(VK_LBUTTON) == 1 && BuyItem(300))
			{
				asset.sounds[L"sound/shopbuybutton.wav"]->Play();
				gameUI->itemList[1]->visible = true;

				if (gameManager.isKnight)
					whiteHero->mp = whiteHero->maxMp += 50;
				else
					blackHero->mp = blackHero->maxMp += 50;
			}
		}
		else if (gameUI->buyBtn[0][2]->rectWithPos().contain(world.getMousePos()) && !gameUI->itemList[2]->visible)
		{
			if (world.getKeyState(VK_LBUTTON) == 1 && BuyItem(300))
			{
				asset.sounds[L"sound/shopbuybutton.wav"]->Play();
				gameUI->itemList[2]->visible = true;

				if (gameManager.isKnight)
					whiteHero->power += 10;
				else
					blackHero->speed += 10;
			}
		}
		else if (gameUI->buyBtn[1][0]->rectWithPos().contain(world.getMousePos()) && !gameUI->itemList[3]->visible)
		{
			if (world.getKeyState(VK_LBUTTON) == 1 && BuyItem(500))
			{
				asset.sounds[L"sound/shopbuybutton.wav"]->Play();
				gameUI->itemList[3]->visible = true;

				if (gameManager.isKnight)
					whiteHero->power += 20;
				else
					blackHero->power += 20;
			}
		}
		else if (gameUI->buyBtn[1][1]->rectWithPos().contain(world.getMousePos()) && !gameUI->itemList[4]->visible)
		{
			if (world.getKeyState(VK_LBUTTON) == 1 && BuyItem(500))
			{
				asset.sounds[L"sound/shopbuybutton.wav"]->Play();
				gameUI->itemList[4]->visible = true;

				if (gameManager.isKnight)
					whiteHero->armor += 5;
				else
					blackHero->armor += 5;
			}
		}
		else if (gameUI->buyBtn[1][2]->rectWithPos().contain(world.getMousePos()) && !gameUI->itemList[5]->visible)
		{
			if (world.getKeyState(VK_LBUTTON) == 1 && BuyItem(500))
			{
				asset.sounds[L"sound/shopbuybutton.wav"]->Play();
				gameUI->itemList[5]->visible = true;

				if (gameManager.isKnight)
					whiteHero->speed += 50;
				else
					blackHero->speed += 50;
			}
		}
	}
	for_iter(eff, effectList)
	{
		if ((*eff)->currentFrame >= (*eff)->textures.size() - 1)
		{
			removeChild(*eff);
			eff = effectList.erase(eff);
			if (eff == effectList.end())
				break;
		}
	}
}

void GameScene::render()
{
	Scene::render();

	objectList.sort([](Object *obj1, Object *obj2) {
		return obj1->center().y < obj2->center().y;
	});

	for_iter(iter, objectList)
		(*iter)->render();

	for_iter(iter, effectList)
		(*iter)->render();

	gameUI->render();
}

void GameScene::init()
{
	addChild(new Sprite("image/map/map/mapBg1.dds"));
	addChild(back = new Sprite("image/map/map/mapBg2.dds"));
	addChild(new Sprite("image/map/map/map.dds"));
	addChild(backLight = new Sprite("image/map/map/mapLight.png"));
	whiteHero = new WhiteHero();
	addChild(whiteHero);
	whiteHero->pos = whiteMinionSpawnPos - Vec2(150, 150);
	whiteHero->targetPos = whiteHero->ColPivotWithPos();

	blackHero = new BlackHero();
	addChild(blackHero);
	follow(blackHero);
	blackHero->pos = blackMinionSpawnPos - Vec2(150, 150);
	blackHero->targetPos = blackHero->ColPivotWithPos();

	if (gameManager.isKnight)
	{
		blackHero->isAI = true;
		blackHero->animation[Unit::STOP]->visible = false;
		follow(whiteHero);
	}
	else
	{
		whiteHero->isAI = true;
		whiteHero->animation[Unit::STOP]->visible = false;
		follow(blackHero);
	}

	whiteNexus = new Nexus(Object::WHITE);
	addChild(whiteNexus);
	whiteNexus->pos = Vec2(91, 2335);

	blackNexus = new Nexus(Object::BLACK);
	addChild(blackNexus);
	blackNexus->pos = Vec2(2335, -73);

	Tower *whiteT1 = new Tower(Object::WHITE);
	addChild(whiteT1);
	whiteT1->pos = Vec2(698, 1676);

	Tower *whiteT2 = new Tower(Object::WHITE);
	addChild(whiteT2);
	whiteT2->pos = Vec2(1314, 1554);

	Tower *blackT1 = new Tower(Object::BLACK);
	addChild(blackT1);
	blackT1->pos = Vec2(1444, 865);

	Tower *blackT2 = new Tower(Object::BLACK);
	addChild(blackT2);
	blackT2->pos = Vec2(2183, 632);
}

void GameScene::Respawn(Object::TeamType type)
{
	if (type == Object::WHITE)
	{
		whiteHero = new WhiteHero();
		addChild(whiteHero);
		whiteHero->pos = whiteMinionSpawnPos - Vec2(150, 150);
		whiteHero->targetPos = whiteHero->ColPivotWithPos();
	
		if (gameManager.isKnight)
			follow(whiteHero);
		else
		{
			whiteHero->isAI = true;
			whiteHero->animation[Unit::STOP]->visible = false;
		}
	}
	else
	{
		blackHero = new BlackHero();
		addChild(blackHero);
		blackHero->pos = blackMinionSpawnPos - Vec2(150, 150);
		blackHero->targetPos = blackHero->ColPivotWithPos();

		if (gameManager.isKnight)
		{
			blackHero->isAI = true;
			blackHero->animation[Unit::STOP]->visible = false;
		}
		else
			follow(blackHero);
	}
}

bool GameScene::BuyItem(int useMoney)
{
	if (money >= useMoney)
	{
		money -= useMoney;
		return true;
	}
	return false;
}
#include "DXUT.h"
#include "MainScene.h"
#include "GameScene.h"
#include "World.h"
#include "GameManager.h"
#include "Asset.h"

MainScene::MainScene()
{
	addChild(new Sprite("image/UI/title/maintitle.png"));
	
	addChild(gameStart = new Sprite("image/UI/title/gamestart.png"));
	gameStart->pos = Vec2(496, 371);
	gameStart->scaleCenter = gameStart->rect.center();
	addChild(howToPlay = new Sprite("image/UI/title/howto.png"));
	howToPlay->pos = Vec2(493, 447);
	howToPlay->scaleCenter = howToPlay->rect.center();
	addChild(introduce = new Sprite("image/UI/title/intro.png"));
	introduce->pos = Vec2(509, 523);
	introduce->scaleCenter = introduce->rect.center();
	addChild(exitB = new Sprite("image/UI/title/exit.png"));
	exitB->pos = Vec2(516, 599);
	exitB->scaleCenter = exitB->rect.center();

	addChild(howToPlay1 = new Sprite("image/UI/howto/howto1.png"));
	howToPlay1->visible = false;
	addChild(howToPlay2 = new Sprite("image/UI/howto/howto2.png"));
	howToPlay2->visible = false;
	addChild(intro1 = new Sprite("image/UI/intro/intro.png"));
	intro1->visible = false;

	addChild(charSelectBack = new Sprite("image/UI/chracterselect/select1.png"));
	charSelectBack->visible = false;
	addChild(knightSelect = new Sprite("image/UI/chracterselect/paladin.png"));
	knightSelect->visible = false;
	addChild(devilSelect = new Sprite("image/UI/chracterselect/demon.png"));
	devilSelect->visible = false;
	devilSelect->pos = Vec2(566, 0);

	addChild(op = new Animation("image/UI/op", 25, 10, false));
	op->stop = true;
	op->visible = false;

	asset.sounds[L"sound/titleBGM.wav"]->Play();
}


MainScene::~MainScene()
{
}

void MainScene::update(float dt)
{
	Scene::update(dt);

	if (!asset.sounds[L"sound/titleBGM.wav"]->IsSoundPlaying())
		asset.sounds[L"sound/titleBGM.wav"]->Play();

	if (op->visible)
	{
		if (op->currentFrame >= op->textures.size() - 1)
		{
			world.changeScene(new GameScene());
			return;
		}
	}
	else if (!howToPlay1->visible && !howToPlay2->visible && !intro1->visible && !charSelectBack->visible)
	{
		if (gameStart->rectWithPos().contain(world.getMousePos()))
		{
			gameStart->scale = Vec2(1.2f, 1.2f);

			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				charSelectBack->visible = true;
				asset.sounds[L"sound/buttonclick.wav"]->Play();
			}
		}
		else
			gameStart->scale = Vec2(1, 1);

		if (howToPlay->rectWithPos().contain(world.getMousePos()))
		{
			howToPlay->scale = Vec2(1.2f, 1.2f);

			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				howToPlay1->visible = true;
				asset.sounds[L"sound/buttonclick.wav"]->Play();
			}
		}
		else
			howToPlay->scale = Vec2(1, 1);

		if (introduce->rectWithPos().contain(world.getMousePos()))
		{
			introduce->scale = Vec2(1.2f, 1.2f);

			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				intro1->visible = true;
				asset.sounds[L"sound/buttonclick.wav"]->Play();
			}
		}
		else
			introduce->scale = Vec2(1, 1);

		if (exitB->rectWithPos().contain(world.getMousePos()))
		{
			exitB->scale = Vec2(1.2f, 1.2f);

			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				asset.sounds[L"sound/buttonclick.wav"]->Play();
				exit(0);
			}
		}
		else
			exitB->scale = Vec2(1, 1);
	}
	else if (charSelectBack->visible)
	{
		if (knightSelect->rectWithPos().contain(world.getMousePos()))
		{
			knightSelect->visible = true;
			devilSelect->visible = false;
			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				asset.sounds[L"sound/buttonclick.wav"]->Play();
				gameManager.isKnight = true;

				op->visible = true;
				op->stop = false;
			}
		}
		else if (!knightSelect->rectWithPos().contain(world.getMousePos()))
		{
			knightSelect->visible = false;
			if (devilSelect->rectWithPos().contain(world.getMousePos()))
			{
				devilSelect->visible = true;
				if (world.getKeyState(VK_LBUTTON) == 1)
				{
					asset.sounds[L"sound/buttonclick.wav"]->Play();
					gameManager.isKnight = false;

					op->visible = true;
					op->stop = false;
				}
			}
			else
				devilSelect->visible = false;
		}
	}
	else if (world.getKeyState(VK_LBUTTON) == 1)
	{
		asset.sounds[L"sound/buttonclick.wav"]->Play();
		if (howToPlay1->visible)
		{
			howToPlay1->visible = false;
			howToPlay2->visible = true;
		}
		else if (howToPlay2->visible)
			howToPlay2->visible = false;
		else if (intro1->visible)
			intro1->visible = false;
	}
}

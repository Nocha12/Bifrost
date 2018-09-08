#include "DXUT.h"
#include "EndingScene.h"
#include "World.h"
#include "MainScene.h"
#include "Asset.h"

EndingScene::EndingScene(bool isKnightWin)
{
	addChild(new Sprite("image/UI/ed/black.png"));
	if (isKnightWin)
		ed = new Animation("image/UI/ed/knightWin", 25, 10, false);
	else
		ed = new Animation("image/UI/ed/evilWin", 26, 10, false);
	ed->stop = true;
	addChild(ed);
}

EndingScene::~EndingScene()
{
}

void EndingScene::update(float dt)
{
	Scene::update(dt);
	if (world.getKeyState(VK_RETURN) == 1)
	{
		asset.sounds[L"sound/goodJob.wav"]->Play();
		if (ed->currentFrame >= ed->textures.size() - 1)
		{
			world.changeScene(new MainScene());
			return;
		}

		ed->stop = false;
	}
}

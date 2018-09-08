#include "DXUT.h"
#include "LoadScene.h"
#include "Asset.h"
#include "GameScene.h"
#include "World.h"
#include "MainScene.h"

LoadScene::LoadScene()
{
	addChild(new Sprite("image/UI/loading/loadingbg.png"));
	addChild(barBack = new Sprite("image/UI/loading/loadingbar1.png"));
	barBack->pos = Vec2(58, 620);
	addChild(bar = new Sprite("image/UI/loading/loadingbar2.png"));
	bar->pos = Vec2(64, 627);
	bar->visibleRect.right = 0;
	addChild(loading = new Animation("image/UI/loading", 2, 3, true, false));
	loading->pos = Vec2(47, 45);

	asset.ready("image");
	asset.getSound(L"sound/titleBGM.wav");
	asset.getSound(L"sound/buttonclick.wav");
	asset.getSound(L"sound/baseattack.wav");
	asset.getSound(L"sound/ingameBGM.wav");
	asset.getSound(L"sound/nightskill2.wav");
	asset.getSound(L"sound/shopbuybutton.wav");
	asset.getSound(L"sound/goodJob.wav");
}

LoadScene::~LoadScene()
{
}

void LoadScene::update(float dt)
{
	Scene::update(dt);

	for (int i = 0; i < 20; i++){
		asset.loadNext();
		if (asset.fileLoaded == asset.fileToLoad)
		{
			world.changeScene(new MainScene());
			return;
		}
	}

	bar->visibleRect.right = bar->rect.right * asset.fileLoaded / asset.fileToLoad;
}

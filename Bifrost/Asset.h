#pragma once
#include "Define.h"
#include "Texture.h"

class Asset
{
public:
	Asset();
	~Asset();

	void init();
	void dispose();
	void ready(string rootPath);
	void loadNext();

	Texture* getTexture(path p);
	CSound* getSound(wpath p);

	map<path, Texture*> textures;
	map<wpath, CSound*> sounds;
	CSoundManager _s;

	list<path> paths;
	list<path>::iterator pathIter;

	int fileToLoad;
	int fileLoaded;
};

extern Asset asset;

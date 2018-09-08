#include "DXUT.h"
#include "Asset.h"

Asset::Asset() : fileToLoad(0), fileLoaded(0)
{
}

Asset::~Asset()
{
}

void Asset::init()
{
	_s.Initialize(DXUTGetHWND(), DSSCL_PRIORITY);
}

void Asset::dispose()
{
	for_iter(iter, textures)
		SAFE_DELETE(iter->second);
	for_iter(iter, sounds)
		SAFE_DELETE(iter->second);
}

void Asset::ready(string rootFolderPath)
{
	for (recursive_directory_iterator iter(rootFolderPath); iter != recursive_directory_iterator(); iter++)
	{
		string extension = iter->path().extension();
		if (extension == ".png" || extension == ".dds")
			paths.push_back(iter->path());
	}

	fileToLoad = paths.size();
	pathIter = paths.begin();
}

void Asset::loadNext()
{
	getTexture(*pathIter);
	pathIter++;
}

Texture* Asset::getTexture(path p)
{
	if (!exists(p))
		cout << "NOT FILE : " << p << endl;
	if (!textures[p])
	{
		textures[p] = new Texture();
		D3DXCreateTextureFromFileExA(
			DXUTGetD3D9Device(),
			p.string().data(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			1,
			NULL,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			NULL,
			&textures[p]->info,
			NULL,
			&textures[p]->d3dSprite
		);
		++fileLoaded;
	}
	
	return textures[p];
}

CSound* Asset::getSound(wpath p)
{
	if (!sounds[p])
		_s.Create(&sounds[p], const_cast<LPWSTR>(p.string().data()));

	return sounds[p];
}


Asset asset;
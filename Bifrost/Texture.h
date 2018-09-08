#pragma once
class Texture
{
public:
	Texture();
	~Texture();

	LPDIRECT3DTEXTURE9 d3dSprite;
	D3DXIMAGE_INFO info;
};


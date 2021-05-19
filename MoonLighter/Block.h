#pragma once
#include "Object.h"

class Block : public Object
{
private:
	TILETYPE tileType;

	int frameX;
	int frameY;

public:
	HRESULT Init() override;
	HRESULT Init(TILE_INFO tile);
	HRESULT Init(RECTFLOAT rc);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Hit();
	void Broken();
};


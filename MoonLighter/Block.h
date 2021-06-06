#pragma once
#include "Object.h"

class Block : public Object
{
private:
	TILETYPE tileType;
	TILETYPE* fromTileType;
	int frameX;
	int frameY;

public:
	HRESULT Init() override;
	HRESULT Init(TILE_INFO tile, TILETYPE* from);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Hit(Object* attacker, Image* hitEffect);
	void Broken();
};


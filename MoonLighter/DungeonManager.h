#pragma once
#include "GameObject.h"

enum class EXIT
{
	LEFT = 1,
	TOP = 2,
	RIGHT = 4,
	BOTTOM = 8,
	NONE = 5
};

struct Dungeon
{
	TILE_INFO tileMap[TILE_X * TILE_Y];
	EXIT exit;
};

class DungeonManager : public GameObject
{
	
private:

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	virtual ~DungeonManager() {};
};


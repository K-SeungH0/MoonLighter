#pragma once
#include "GameObject.h"

enum class EXIT
{
	LEFT = 1,
	TOP = 2,
	RIGHT = 4,
	BOTTOM = 8,
	NONE = 0
};

struct Dungeon
{
	int roomIndex;
	TILE_INFO tileMap[DUNGEON_TILE_X * DUNGEON_TILE_Y];
	EXIT exit;
};

class DungeonManager : public GameObject
{
	
private:
	vector<Dungeon> vDungeon;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void RoomCreate();
	void DungeonLoad();
	virtual ~DungeonManager() {};
};


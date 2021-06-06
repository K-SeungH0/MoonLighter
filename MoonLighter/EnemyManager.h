#pragma once
#include "GameObject.h"
#include "AstarScene.h"

#define ASTAR_TILESIZE 64

class Enemy;
class ItemManager;

class EnemyManager : public GameObject
{
private:
	vector<Enemy*> vEnemys;
	vector<POINT> vRespawnPos;
	ItemManager* lpItemManager;
	
	// Astar
	POINTFLOAT* endPos;
	TILE_INFO* astarMap;
	AstarScene astar;

	bool test;

public:
	HRESULT Init() override;
	HRESULT Init(TILE_INFO* astarMap, POINTFLOAT* endPos, ItemManager* lpItemManager);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void AddRespawn(POINT pos);
	void RespawnShuffle();
	void EnemySpawn();
	GameData::ItemData GetRandomItem();
	inline vector<Enemy*> GetEnemys() { return this->vEnemys; }
	void ImageLoad();
};


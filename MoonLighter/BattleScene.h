#pragma once
#include "GameObject.h"

class Player;
class Image;
class ProjectileManager;
class Object;
class Inventory;
class BattleSceneUI;
class ItemManager;
class Camera;
class DungeonManager;
class EnemyManager;

class BattleScene : public GameObject
{
private:
	Camera* lpCamera;

	Image* lpBackGround;
	DungeonManager* lpDungeonManager;
	TILE_INFO tileMap[DUNGEON_TILE_X * DUNGEON_TILE_Y];
	Player* lpPlayer;
	BattleSceneUI* lpUI;

	vector<Object*> vObjects;
	
	ItemManager* lpItemManager;

	Object* testItem;
	
	EnemyManager* lpEnemyManager;

	char text[128];
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Load();
	void ImageLoad();

	void TestItem();
};


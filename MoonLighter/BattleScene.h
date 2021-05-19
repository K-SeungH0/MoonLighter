#pragma once
#include "GameObject.h"

class Player;
class Image;
class ProjectileManager;
class Object;
class Inventory;
class BattleSceneUI;
class BattleScene : public GameObject
{
private:
	Object* outsideColliderTop;
	Object* outsideColliderLeft;
	Object* outsideColliderRight;
	Object* outsideColliderBottom;
	
	Image* backGround;
	Image* tileImage;
	TILE_INFO tileMap[TILE_X * TILE_Y];
	Player* lpPlayer;
	BattleSceneUI* lpUI;

	vector<Object*> vObjects;

	char text[128];
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Load();
	void ImageLoad();
};


#pragma once
#include "GameObject.h"

class Player;
class Image;
class ProjectileManager;
class Object;
class BattleScene : public GameObject
{
private:
	Image* backGround;
	Image* tileImage;
	TILE_INFO tileMap[TILE_X * TILE_Y];
	Player* lpPlayer;

	vector<Object*> vObjects;

	char text[128];
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void CheckCollision();
	void Load();
	void ImageLoad();
};


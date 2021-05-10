#pragma once
#include "GameObject.h"

class Player;
class Image;
class ProjectileManager;
class BattleScene : public GameObject
{
private:
	typedef struct tagTile
	{
		RECT rcTile;
		int frameX;
		int frameY;
	}TILE_INFO;

	TILE_INFO tileInfo[16];
	Image* testSample;

	//ProjectileManager* projectilemManager;
	//Player* player;
	Image* backGroundImage;

	POINTFLOAT player;
	RECT missile;
	bool isFired;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void CheckCollision();
};


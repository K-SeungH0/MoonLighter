#pragma once
#include "GameObject.h"

class Image;
class Camera;
class Player;
class Object;
class LayerManager;
class BattleSceneUI;

class TownScene : public GameObject
{
private:
	Image* lpBackGround;
	Camera* lpCamera;
	Player* lpPlayer;
	Image* lpInteract;
	Image* lpPixelImage;
	HDC pixelDC;
	LayerManager* lpLayerManager;
	vector<POINTFLOAT> testPos;
	BattleSceneUI* lpUI;


	vector<pair<Image*, POINTFLOAT>> vObjects;
	//vector<Object*> vObjects;
	vector<pair<Image*, POINTFLOAT>> vObjectsPixel;
	TILE_INFO tileMap[TOWN_TILE_X * TOWN_TILE_Y];

	bool isEnterDunGeon;
	float timer;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Load();
	void MapLoad();
	void ImageLoad();
};


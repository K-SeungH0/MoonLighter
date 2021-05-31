#pragma once
#include "GameObject.h"

class Image;
class Camera;
class player;
class BattleSceneUI;
class ShopScene : public GameObject
{
private:
	Image* lpBackGround;
	Image* lpMidImage;
	Image* lpBackGroundPixel;
	Image* lpDoor;
	Image* lpInteract;
	HDC pixelDC;

	Camera* lpCamera;
	Player* lpPlayer;
	BattleSceneUI* lpUI;

	int doorFrameX;
	int doorFrameY;

	bool isExit;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void ImageLoad();
};


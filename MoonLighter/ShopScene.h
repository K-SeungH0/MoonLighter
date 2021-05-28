#pragma once
#include "GameObject.h"

class Image;
class Camera;
class player;
class ShopScene : public GameObject
{
private:
	Image* lpBackGround;
	Image* lpMidImage;
	Image* lpBackGroundPixel;
	Image* lpDoor;
	Image* lpInteract;

	Camera* lpCamera;
	Player* lpPlayer;

	int doorFrameX;
	int doorFrameY;

	bool exitAble;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void ImageLoad();
};


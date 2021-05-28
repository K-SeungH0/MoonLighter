#pragma once
#include "GameObject.h"

class Image;
class Camera;
class Player;
class TownScene : public GameObject
{
private:
	Image* lpBackGround;
	Camera* lpCamera;
	Player* lpPlayer;
	Image* lpInteract;

	bool isEnterDunGeon;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void ImageLoad();

};

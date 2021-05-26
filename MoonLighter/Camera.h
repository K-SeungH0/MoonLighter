#pragma once
#include "GameObject.h"

class Image;
class Player;
class Object;
class Camera : public GameObject
{
private:
	POINTFLOAT cameraPos;
	Player* foucs;
	Image* lpBackGround;

public:
	HRESULT Init() override;
	HRESULT Init(Player* foucs , Image* lpBackGround);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void CameraRender(HDC hdc, POINT wolrdPos, Image* lpImage);
	
	
	inline void SetCameraPos(POINTFLOAT cameraPos) { this->cameraPos = cameraPos; }
};


#pragma once
#include "GameObject.h"

class Image;
class Object;
class Camera : public GameObject
{
private:
	POINTFLOAT cameraPos;
	POINTFLOAT* foucsPos;

	Image* lpBackGround;
	float moveSpeed;

public:
	HRESULT Init() override;
	HRESULT Init(Image* lpBackGround, POINTFLOAT* foucsPos, float moveSpeed);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void CameraRender(HDC hdc, POINT worldPos, Image* lpImage);
	void CameraFrameRender(HDC hdc, Image* lpImage, POINT worldPos,
		int currFrameX, int currFrameY, float size = 1, bool isCenterRenderring = false);
	
	inline void SetCameraPos(POINTFLOAT cameraPos) { this->cameraPos = cameraPos; }
	inline POINTFLOAT GetCameraPos() { return this->cameraPos; }
	inline POINTFLOAT* GetpCameraPos() { return &this->cameraPos; }
};


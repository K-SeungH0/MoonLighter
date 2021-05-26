#include "Camera.h"
#include "Image.h"
#include "Player.h"
HRESULT Camera::Init()
{
	return S_OK;
}

HRESULT Camera::Init(Player* foucs, Image* lpBackGround)
{
	this->foucs = foucs;
	this->lpBackGround = lpBackGround;
	return S_OK;
}

void Camera::Release()
{

}

void Camera::Update()
{
	if (foucs->GetPos().x - cameraPos.x > WINSIZE_X * 3 / 4 &&
		cameraPos.x < lpBackGround->GetWidth() - WINSIZE_X)
	{
		cameraPos.x += DELTATIME * (foucs->GetMoveSpeed() + foucs->GetAdditionalMoveSpeed());
	}
	if (foucs->GetPos().y - cameraPos.y > WINSIZE_Y * 3 / 4 &&
		cameraPos.y < lpBackGround->GetHeight() - WINSIZE_Y)
	{
		cameraPos.y += DELTATIME * (foucs->GetMoveSpeed() + foucs->GetAdditionalMoveSpeed());
	}
	if (foucs->GetPos().x - cameraPos.x < WINSIZE_X / 4 &&
		cameraPos.x > 0)
	{
		cameraPos.x -= DELTATIME * (foucs->GetMoveSpeed() + foucs->GetAdditionalMoveSpeed());
	}
	if (foucs->GetPos().y - cameraPos.y < WINSIZE_Y / 4 &&
		cameraPos.y > 0)
	{
		cameraPos.y -= DELTATIME * (foucs->GetMoveSpeed() + foucs->GetAdditionalMoveSpeed());
	}

	if (cameraPos.x <= 0)
	{
		cameraPos.x = 0;
	}
	if (cameraPos.y <= 0)
	{
		cameraPos.y = 0;
	}
	if (cameraPos.x >= lpBackGround->GetWidth() - WINSIZE_X)
	{
		cameraPos.x = lpBackGround->GetWidth() - WINSIZE_X;
	}
	if (cameraPos.y >= lpBackGround->GetHeight() - WINSIZE_Y)
	{
		cameraPos.y = lpBackGround->GetHeight() - WINSIZE_Y;
	}
}

void Camera::Render(HDC hdc)
{
	CameraRender(hdc, { 0, 0 }, lpBackGround);
	POINTFLOAT test;
	test.x = foucs->GetPos().x - cameraPos.x;
	test.y = foucs->GetPos().y - cameraPos.y;
	foucs->TestRender(hdc, test);
	//CameraRender(hdc, { (LONG)foucs->GetPos().x, (LONG)foucs->GetPos().y }, foucs->GetImage());
}

void Camera::CameraRender(HDC hdc, POINT worldPos, Image* lpImage)
{
	//if (cameraPos.x > worldPos.x || cameraPos.y > worldPos.y ||
	//	cameraPos.x + WINSIZE_X < worldPos.x - lpImage->GetWidth() ||
	//	cameraPos.y + WINSIZE_Y < worldPos.y - lpImage->GetHeight())
	//	return;
	
	lpImage->CameraRender(hdc, worldPos.x , worldPos.y, cameraPos.x, cameraPos.y);
}
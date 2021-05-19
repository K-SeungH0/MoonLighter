#include "UI.h"
#include "Image.h"
HRESULT UI::Init()
{
	return S_OK;
}

HRESULT UI::Init(Image* lpImage, POINT pos)
{
	this->lpImage = lpImage;
	this->pos = pos;
	return S_OK;
}

void UI::Release()
{
	delete this;
}

void UI::Update()
{

}

void UI::Render(HDC hdc)
{
	lpImage->FrameRender(hdc, 0, 0, 0, 0);
}

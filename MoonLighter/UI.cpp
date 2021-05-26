#include "UI.h"
#include "Image.h"
HRESULT UI::Init()
{
	return S_OK;
}

HRESULT UI::Init(Image* lpImage, POINT pos, int frameX, int frameY, int cutX, int cutY)
{
	this->lpImage = lpImage;
	this->pos = pos;
	this->frameX = frameX;
	this->frameY = frameY;
	this->cutX = cutX;
	this->cutY = cutY;
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
	lpImage->CutRender(hdc, pos.x, pos.y, frameX, frameY, cutX, cutY);
}

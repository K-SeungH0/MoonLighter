#pragma once
#include "GameObject.h"

class Image;

class UI : public GameObject
{
protected:
	Image* lpImage;
	POINT pos;

public:
	HRESULT Init() override;
	HRESULT Init(Image* lpImage, POINT pos);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	virtual ~UI() {};
};


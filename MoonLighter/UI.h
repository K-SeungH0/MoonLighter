#pragma once
#include "GameObject.h"

class Image;

class UI : public GameObject
{
protected:
	Image* lpImage;
	POINTFLOAT pos;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	virtual ~UI() {};
};


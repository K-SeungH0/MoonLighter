#pragma once
#include "GameObject.h"
class Image;
class Player : public GameObject
{
private:
	Image* image;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	~Player() override {};
};


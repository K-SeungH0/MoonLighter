#pragma once
#include "Unit.h"

class Enemy : public Unit
{
private:
	STATE state;

	int imageFrame;
	int dirFrame;
	
	float frameTimer;
public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Move();
	void Attack();
	void ImageLoad();
};


#pragma once
#include "Object.h"

class Image;

class Item : public Object
{
protected:
	//Image* lpItemImage;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Use();

	//inline Image* GetImage() { return this->lpItemImage; }

	~Item() override {};
};


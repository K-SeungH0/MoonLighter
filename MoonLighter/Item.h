#pragma once
#include "Object.h"

class Image;

enum class ITEMCODE
{
	ITEM0,
	ITEM1,
	ITEM2,
	ITEM3,
	ITEM4,
	ITEM5,
	ITEM6,
	ITEM7,
	ITEM8,
	ITEM9,
	ITEM10,
	ITEM11,
	ITEM12,
	POTION0,
	POTION1,
	POTION2,
	POTION3,
	NONE
};


class Item : public Object
{
protected:
	//Image* lpItemImage;
	bool isEquipment;
	ITEMCODE itemCode;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Use();
	void PickUp();
	//inline Image* GetImage() { return this->lpItemImage; }

	~Item() override {};
};
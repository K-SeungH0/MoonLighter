#pragma once
#include "Object.h"

class Image;
class Inventory;
class ItemManager;

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
	GameData::ItemData itemData;
	ItemManager* lpItemManager;
	string description;

public:
	HRESULT Init() override;
	HRESULT Init(GameData::ItemData itemData, ItemManager* lpItemManager);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Render(HDC hdc, POINT pos);

	void Use();
	void PickUp();
	void ReSetCollider();
	
	inline GameData::ItemData GetItemData() { return this->itemData; }
	inline string GetDescription() { return this->description; }
	inline ItemManager* GetItemManager() { return this->lpItemManager; }

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; ReSetCollider(); }
	inline void SetItemData(GameData::ItemData itemData) { this->itemData = itemData; }
	inline void SetDescription(string description) { this->description = description; }
	~Item() override {};
};
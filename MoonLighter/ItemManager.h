#pragma once
#include "GameObject.h"

class Item;
class Inventory;
class ItemManager : public GameObject
{
private:
	vector<Item*> vItems;
	Inventory* lpInventory;
public:
	HRESULT Init() override;
	HRESULT Init(Inventory* lpInventory);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void AddItem(Item* item, GameData::ItemData itemData, POINTFLOAT pos);
	void RemoveItem(Item* item);

	inline Inventory* GetInventory() { return this->lpInventory; }

	~ItemManager() override{};
};


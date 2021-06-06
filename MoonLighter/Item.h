#pragma once
#include "Object.h"

class Image;
class Inventory;
class ItemManager;
enum class SLOTTYPE;
struct Slot;
class Item : public Object
{
protected:
	GameData::ItemData itemData;
	Image* lpItemImage;
	ItemManager* lpItemManager;
	string description;

	int armor;
	int hp;
	int speed;
	SLOTTYPE slotType;
	Slot* lpOwnerSlot;

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
	inline Image* GetItemImage() { return this->lpItemImage; }
	inline string GetDescription() { return this->description; }
	inline ItemManager* GetItemManager() { return this->lpItemManager; }
	inline int GetArmor() { return this->armor; }
	inline int GetHp() { return this->hp; }
	inline int GetSpeed() { return this->speed; }
	inline SLOTTYPE GetSlotType() { return this->slotType; }

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; ReSetCollider(); }
	inline void SetItemData(GameData::ItemData itemData) { this->itemData = itemData; }
	inline void SetDescription(string description) { this->description = description; }
	inline void SetSaveSlotPos(POINT slotPos) { this->itemData.slotPos = slotPos; }
	inline void SetSaveCount(int count) { this->itemData.count = count; }
	inline void SetSaveIsInEquip(bool isInEquip) { this->itemData.isInEquip = isInEquip; }
	inline void SetOnwer(Slot* lpOwnerSlot) { this->lpOwnerSlot = lpOwnerSlot; }

	~Item() override {};
};
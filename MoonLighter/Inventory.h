#pragma once
#include "UI.h"

#define SLOT_X 5
#define SLOT_Y 4

class Image;
class Item;

struct Slot
{
	Image* lpSlotImage;
	POINT slotPos;
	Item* lpItem = nullptr;
	int count = 0;
};
class Inventory : public UI
{
private:
	bool isActive;
	
	Slot invenSlots[SLOT_Y][SLOT_X];
	Slot equipSlots[SLOT_Y][2];
	Slot selectSlots;
	Slot selectItem;

	int selectSlotX;
	int selectSlotY;

	bool isEquipSelect;
	bool isItemPickUp;
	char text[128];

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
	void ImageLoad();
	
	void AddItem(Item* item);
	void ToggleActive();
	void ItemPickUp();

	inline bool GetActive() { return this->isActive; }
	~Inventory() override {};
};

